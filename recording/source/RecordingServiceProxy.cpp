#include <gio/gio.h>
#include <glib.h>
#include <glib/gerror.h>
#include <gio/gioenums.h>
#include <gio/gdbusconnection.h>
#include <unistd.h>
#include "../include/RecordingServiceProxy.h"
#include "IRecordingServiceListener.h"

static const char* SERVICE_BUS_NAME = "fxn.camera.recording";
static const char* SERVICE_OBJECT_PATH = "/fxn/camera/recording";
static const char* SERVICE_INTERFACE_NAME = "fxn.camera.recording";

static GDBusConnection *pConnection = nullptr;
static GDBusProxy *pProxy = nullptr;
static bool s_IsConnectionDisconnetecd = false;
static IRecordingServiceListener* sp_IServiceListener;
static gulong signal_handler_id;
static pthread_mutex_t m_mutex;

static void HandleOnSignal (GDBusProxy  *proxy,
                            const gchar *sender_name,
                            const gchar *signal_name,
                            GVariant    *parameters,
                            gpointer     user_data) {

    if (strcmp("onRecordingEvent", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onRecordingEvent(pdata);
        }
    }
    else {
        printf("HandleOnSignal: signal name=%s", signal_name);
    }
}

RecordingServiceProxy::RecordingServiceProxy(){

}



RecordingServiceProxy::~RecordingServiceProxy(){

}

int RecordingServiceProxy::SetListener(IRecordingServiceListener* plistener) {
    sp_IServiceListener = plistener;
    return 0;
}

int RecordingServiceProxy::Init() {
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_create(&m_thread_tid, nullptr, &RecordingServiceProxy::innerThread, this);
    return 0;
}

int RecordingServiceProxy::Deinit() { return 0; }

bool RecordingServiceProxy::IsReady() {
    return m_IsReady;
}


int RecordingServiceProxy::SetConfig(const std::string& str, std::string& result){
    InvokeSetMethod("SetConfig", str, result);
	return 0;
}


int RecordingServiceProxy::GetConfig(std::string& result){
    InvokeGetMethod("GetConfig", result);
	return 0;
}



int RecordingServiceProxy::GetAPIVersion(std::string& result){
    GVariant *variant;
    const gchar* str;
    variant = g_dbus_proxy_get_cached_property (pProxy, "Version");
    if (variant == nullptr) {
        result = "error";
        return -1;
    }
    str = g_variant_get_string(variant, nullptr);
    result = std::string(str);
    g_variant_unref (variant);
    return 0;
}

int RecordingServiceProxy::InvokeSetMethod(std::string const& name, std::string const& str, std::string& result) {
    pthread_mutex_lock(&m_mutex);
    if (pProxy == nullptr) {
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

    GError *pError = nullptr;
    GVariant* result2;
    result2 = g_dbus_proxy_call_sync(pProxy, name.c_str(), g_variant_new ("(s)", str.c_str()),
                                     G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &pError);
    if (pError == nullptr) {
        const gchar* str2;
        g_variant_get (result2, "(&s)", &str2);
        result = std::string(str2);
        g_print("CustomCommand: return=%s \n", result.c_str());
        pthread_mutex_unlock(&m_mutex);
        return 0;
    } else {
        g_print("CustomCommand: Failed to call method. Response: %s.\n", pError->message);
        if (pError->code == 2) {
            s_IsConnectionDisconnetecd = true;
        }
        g_error_free(pError);
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

}

int RecordingServiceProxy::InvokeGetMethod(std::string const& name, std::string& result) {
    pthread_mutex_lock(&m_mutex);
    if (pProxy == nullptr) {
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

    GError *pError = nullptr;
    GVariant* result2;
    result2 = g_dbus_proxy_call_sync(pProxy, name.c_str(), nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &pError);
    if (pError == nullptr) {
        const gchar* str2;
        g_variant_get (result2, "(&s)", &str2);
        result = std::string(str2);
        g_print("%s: return=%s \n", name.c_str(), result.c_str());
        pthread_mutex_unlock(&m_mutex);
        return 0;
    } else {
        g_print("%s: Failed to call method. Response: %s.\n", name.c_str(), pError->message);
        if (pError->code == 2) {
            s_IsConnectionDisconnetecd = true;
        }
        g_error_free(pError);
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

}

void *RecordingServiceProxy::innerThread(void *arg) {
    auto* mt = reinterpret_cast<RecordingServiceProxy*>(arg);
    if (mt == NULL) {
        pthread_exit(0);
    }
    GError *error;
    while(!mt->m_ThreadExit) {
        pthread_mutex_lock(&m_mutex);
        if (nullptr == pProxy || s_IsConnectionDisconnetecd) {
            bool bRet = TRUE;

            GError *pConnError = nullptr;
            GError *pProxyError = nullptr;
            do {
                bRet = TRUE;

                /** First step: get a connection */
                pConnection = g_bus_get_sync(G_BUS_TYPE_SYSTEM, nullptr, &pConnError);

                if (nullptr == pConnError) {
                    pProxy = g_dbus_proxy_new_sync (pConnection, G_DBUS_PROXY_FLAGS_NONE, NULL, SERVICE_BUS_NAME,
                                                    SERVICE_OBJECT_PATH, SERVICE_INTERFACE_NAME, NULL, &error);
                    if (nullptr == pProxy) {
                        g_print("InitDBusCommunication: Failed to create proxy. Reason: %s.\n", pProxyError->message);
                        g_error_free(pProxyError);
                        bRet = FALSE;
                    } else {
                        g_print("InitDBusCommunication: Successed \n");
                    }

                } else {
                    if (nullptr != pConnError->message) {
                        g_print("InitDBusCommunication: Failed to connect to dbus. Reason: %s.\n", pConnError->message);
                    }
                    g_error_free(pConnError);
                    bRet = FALSE;
                }
                mt->m_IsReady = (bRet == TRUE);
                sleep(1);
            } while(FALSE == bRet);

            signal_handler_id = g_signal_connect (pProxy,
                                                  "g-signal",
                                                  G_CALLBACK (HandleOnSignal),
                                                  NULL);
            s_IsConnectionDisconnetecd = false;
        }
        pthread_mutex_unlock(&m_mutex);

        if (nullptr != pProxy && !s_IsConnectionDisconnetecd) {
            sleep(2);
        }
    }
    pthread_exit(0);
}