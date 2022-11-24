///////////////////////////////////////////////////////////
//  EventsServiceProxy.cpp
//  Implementation of the Class EventsServiceProxy
//  Created on:      24-十一月-2022 下午 04:03:34
//  Original author: bms
///////////////////////////////////////////////////////////
#include <gio/gio.h>
#include <glib.h>
#include <glib/gerror.h>
#include <gio/gioenums.h>
#include <gio/gdbusconnection.h>
#include <unistd.h>
#include "EventsConfig.h"

#include "EventsServiceProxy.h"

static GDBusConnection *pConnection = nullptr;
static GDBusProxy *pProxy = nullptr;
static bool s_IsConnectionDisconnected = false;
static IEventsServiceListener* sp_IServiceListener;
static gulong signal_handler_id;
static pthread_mutex_t m_mutex;

static void HandleOnSignal (GDBusProxy  *proxy,
                            const gchar *sender_name,
                            const gchar *signal_name,
                            GVariant    *parameters,
                            gpointer     user_data) {

    if (strcmp("onDataStorageEvent", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onDataStorageEvent(pdata);
        }
    } else if (strcmp("onCustomEvent", signal_name) == 0) {
        if (nullptr != sp_IServiceListener) {
            const gchar *pdata;
            g_variant_get (parameters, "(&s)", &pdata);
            (void)sp_IServiceListener->onCustomEvent(pdata);
        }
    } else {
        printf("HandleOnSignal: signalname=%s", signal_name);
    }
}

EventsServiceProxy::EventsServiceProxy(){

}

EventsServiceProxy::~EventsServiceProxy(){

}

int EventsServiceProxy::Init(){
    pthread_mutex_init(&m_mutex, nullptr);
    pthread_create(&m_thread_tid, nullptr, &EventsServiceProxy::innerThread, this);
	return 0;
}

int EventsServiceProxy::Deinit(){

	return 0;
}

bool EventsServiceProxy::IsReady(){

	return true;
}

int EventsServiceProxy::SetListener(IEventsServiceListener* plistener) {
    sp_IServiceListener = plistener;
	return 0;
}

int EventsServiceProxy::CustomCommand(string const& str, string& result) {
    InvokeSetMethod("CustomCommand", str, result);
	return 0;
}

int EventsServiceProxy::GetEvents(string const& str, string& result){
    InvokeSetMethod("GetEvents", str, result);
	return 0;
}

int EventsServiceProxy::GetAPIVersion(string &result) {
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

int EventsServiceProxy::InvokeSetMethod(std::string const& name,
                                          std::string const& str, std::string& result) {
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

int EventsServiceProxy::InvokeGetMethod(std::string const& name, std::string& result) {
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

void *EventsServiceProxy::innerThread(void *arg) {
    auto* mt = reinterpret_cast<EventsServiceProxy*>(arg);
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
                    pProxy = g_dbus_proxy_new_sync (pConnection, G_DBUS_PROXY_FLAGS_NONE, NULL, BUS_NAME,
                                                    OBJECT_PATH, INTERFACE_NAME, NULL, &error);
                    if (nullptr == pProxy) {
                        g_print("InitDBusCommunication: Failed to create proxy. Reason: %s.\n", pProxyError->message);
                        g_error_free(pProxyError);
                        bRet = FALSE;
                    } else {
                        g_print("InitDBusCommunication: Successes \n");
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
            s_IsConnectionDisconnected = false;
        }
        pthread_mutex_unlock(&m_mutex);

        if (nullptr != pProxy && !s_IsConnectionDisconnected) {
            sleep(2);
        }
    }
    pthread_exit(0);
}