#include <gio/gio.h>
#include <glib.h>
#include <glib/gerror.h>
#include <gio/gioenums.h>
#include <gio/gdbusconnection.h>
#include <unistd.h>
#include "MISCServiceProxy.h"

static const char* SERVICE_BUS_NAME = "fxn.camera.system";
static const char* SERVICE_OBJECT_PATH = "/fxn/camera/system";
static const char* SERVICE_INTERFACE_NAME = "fxn.camera.system.misc";

static GDBusConnection *pConnection = nullptr;
static GDBusProxy *pProxy = nullptr;
static bool s_IsConnectionDisconnected = false;
static IMISCServiceListener* sp_IServiceListener;
static gulong signal_handler_id;
static pthread_mutex_t m_mutex;

static void HandleOnSignal (GDBusProxy  *proxy,
                            const gchar *sender_name,
                            const gchar *signal_name,
                            GVariant    *parameters,
                            gpointer     user_data) {

    if (strcmp("onPIRStateChanged", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onPIRStateChanged(pdata);
            printf("signalname=%s, value=%s\n", signal_name, pdata);
        }
    } else if (strcmp("onLightSensorLevelChanged", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onLightSensorLevelChanged(pdata);
            printf("onCustomCommandResponse=%s, value=%s\n", signal_name, pdata);
        }
    } else if (strcmp("onCustomStorageSignal", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onCustomMiscSignal(pdata);
            printf("onCustomStorageSignal=%s, value=%s\n", signal_name, pdata);
        }
    } else {

    }
}

MISCServiceProxy::MISCServiceProxy(){
    m_IsReady = false;
}



MISCServiceProxy::~MISCServiceProxy(){

}

int MISCServiceProxy::Init(){
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_create(&m_thread_tid, nullptr, &MISCServiceProxy::innerThread, this);
	return 0;
}

int MISCServiceProxy::Deinit(){

	return 0;
}


bool MISCServiceProxy::IsReady(){
	return m_IsReady;
}


int MISCServiceProxy::SetListener(IMISCServiceListener* plistener){
    sp_IServiceListener = plistener;
	return 0;
}


int MISCServiceProxy::SetTimeZone(const std::string& str, std::string& result){
    InvokeSetMethod("SetTimeZone", str, result);
    return 0;
}

int MISCServiceProxy::GetBatteryVoltage(std::string &result){
    InvokeGetMethod("GetBatteryVoltage", result);
    return 0;
}

int MISCServiceProxy::GetTimeZone(std::string& result){
    InvokeGetMethod("GetTimeZone", result);
    return 0;
}


int MISCServiceProxy::SetTime(const std::string& str, std::string& result){
    InvokeSetMethod("SetTime", str, result);
    return 0;    
}


int MISCServiceProxy::GetTime(std::string& result){
    InvokeGetMethod("GetTime", result);
    return 0;    
}


int MISCServiceProxy::FactoryReset(std::string const& str, std::string &result) {
    pthread_mutex_lock(&m_mutex);
    if (pProxy == nullptr) {
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

    GError *pError = nullptr;
    GVariant* result2;
    result2 = g_dbus_proxy_call_sync(pProxy, "FactoryReset", g_variant_new ("(s)", str.c_str()),
                                     G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &pError);
    if (pError == nullptr) {
        const gchar* str2;
        g_variant_get (result2, "(&s)", &str2);
        result = std::string(str2);
        g_print("FactoryReset: return=%s \n", result.c_str());
        pthread_mutex_unlock(&m_mutex);
        return 0;
    } else {
        g_print("FactoryReset: Failed to call method. Response: %s.\n", pError->message);
        if (pError->code == 2) {
            s_IsConnectionDisconnected = true;
        }
        g_error_free(pError);
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }
}

int MISCServiceProxy::Reboot(std::string& result){
    return InvokeGetMethod("Reboot", result);
}


int MISCServiceProxy::GetSerialNumber(std::string& result){
    return InvokeGetMethod("GetSerialNumber", result);
}


int MISCServiceProxy::GetFirmwareVersion(std::string& result){
    return InvokeGetMethod("GetFirmwareVersion", result);
}


int MISCServiceProxy::GetHostName(std::string& result){
    return InvokeGetMethod("GetHostName", result);
}

int MISCServiceProxy::InvokeSetMethod(std::string const& name, std::string const& str, std::string& result) {
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
        g_print("InvokeSetMethod: return=%s \n", result.c_str());
        pthread_mutex_unlock(&m_mutex);
        return 0;
    } else {
        g_print("InvokeSetMethod: Failed to call method. Response: %s.\n", pError->message);
        if (pError->code == 2) {
            s_IsConnectionDisconnected = true;
        }
        g_error_free(pError);
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

}

int MISCServiceProxy::InvokeGetMethod(std::string const& name, std::string& result) {
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
            s_IsConnectionDisconnected = true;
        }
        g_error_free(pError);
        pthread_mutex_unlock(&m_mutex);
        return -1;
    }

}

int MISCServiceProxy::SetHostName(const std::string& str, std::string& result){
    return InvokeSetMethod("SetHostName", str, result);
}


int MISCServiceProxy::GetNetworkTimeProtocolState(std::string& result){
    return InvokeGetMethod("GetNTPState", result);
}


int MISCServiceProxy::SetNetworkTimeProtocolState(const std::string& str, std::string& result){
    return InvokeSetMethod("SetHostName", str, result);
}


int MISCServiceProxy::SetPIRSensitivity(const std::string& str, std::string& result){
    return InvokeSetMethod("SetPIRSensitivity", str, result);
}


int MISCServiceProxy::GetPIRSensitivity(std::string& result){
    return InvokeGetMethod("GetPIRSensitivity", result);
}


int MISCServiceProxy::SetChimeType(const std::string& str, std::string& result){
    return InvokeSetMethod("SetChimeType", str, result);
}


int MISCServiceProxy::GetChimeType(std::string& result){
    return InvokeGetMethod("GetChimeType", result);
}


int MISCServiceProxy::GetLightSensorLevel(std::string& result){
    return InvokeGetMethod("GetLightSensorLevel", result);
}


int MISCServiceProxy::GetTotalInternalFlashVolume(std::string& result){
    return InvokeGetMethod("GetTotalInternalFlashVolume", result);
}


int MISCServiceProxy::GetFreeInternalFlashVolume(std::string& result){
    return InvokeGetMethod("GetFreeInternalFlashVolume", result);
}

int MISCServiceProxy::CustomCommand(std::string const& str, std::string &result) {
    InvokeSetMethod("CustomCommand", str, result);
    return 0;
}

int MISCServiceProxy::GetAPIVersion(std::string& result){
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

void *MISCServiceProxy::innerThread(void *arg) {
    auto* mt = reinterpret_cast<MISCServiceProxy*>(arg);
    if (mt == NULL) {
        pthread_exit(0);
    }
    GError *error;
    while(!mt->m_ThreadExit) {
        pthread_mutex_lock(&m_mutex);

        if (nullptr != pProxy) {
            gchar *owner_name = g_dbus_proxy_get_name_owner((GDBusProxy*)pProxy);
            if (nullptr == owner_name) {
                s_IsConnectionDisconnected = true;
                mt->m_IsReady = false;
            } else {

            }
        }

        if (nullptr == pProxy || s_IsConnectionDisconnected) {
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
                    }

                } else {
                    if (nullptr != pConnError->message) {
                        g_print("InitDBusCommunication: Failed to connect to dbus. Reason: %s.\n", pConnError->message);
                    }
                    g_error_free(pConnError);
                    bRet = FALSE;
                }
                sleep(1);
            } while(FALSE == bRet);

            signal_handler_id = g_signal_connect (pProxy,
                                                  "g-signal",
                                                  G_CALLBACK (HandleOnSignal),
                                                  NULL);
            mt->m_IsReady = (bRet == TRUE);
            s_IsConnectionDisconnected = false;
        }
        pthread_mutex_unlock(&m_mutex);

        if (nullptr != pProxy && !s_IsConnectionDisconnected) {
            sleep(2);
        }
    }
    pthread_exit(0);
}