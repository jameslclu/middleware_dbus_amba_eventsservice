///////////////////////////////////////////////////////////
//  EventsServiceStub.cpp
//  Implementation of the Class EventsServiceStub
//  Created on:      24-十一月-2022 下午 04:03:35
//  Original author: bms
///////////////////////////////////////////////////////////
#include <string>
#include <unistd.h>
#include <sys/syslog.h>
#include "EventsServiceStub.h"
#include "EventsConfig.h"

using std::string;
static IEventsService *mp_EventsService;
static GMainLoop *loop;
static guint owner_id;
static GDBusConnection* sp_GDBusConnection = nullptr;
static bool s_ready = false;
static GDBusNodeInfo *introspection_data = nullptr;

static const gchar introspection_xml[] = {
        "<node>"
        "  <interface name='fxn.camera.events'>"
        "    <method name='GetEvents'>"
        "      <arg type='s' name='value' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='CustomCommand'>"
        "      <arg type='s' name='value' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <signal name='onDataStorageEvent'>"
        "      <arg type='s' name='value'>"
        "      </arg>"
        "    </signal>"
        "    <signal name='onCustomEvent'>"
        "      <arg type='s' name='value'>"
        "      </arg>"
        "    </signal>"
        "    <property type='s' name='Version' access='read'/>"
        "  </interface>"
        "</node>" };

//===============================================================
void
EventsServiceStub::handle_method_call (GDBusConnection       *connection,
                                         const gchar           *sender,
                                         const gchar           *object_path,
                                         const gchar           *interface_name,
                                         const gchar           *method_name,
                                         GVariant              *parameters,
                                         GDBusMethodInvocation *invocation,
                                         gpointer               user_data) {
    syslog(LOG_DEBUG, "handle_method_call: object_path=%s, interface_name=%s\n", object_path, interface_name);

    std::string result = "invalid";

    if (g_strcmp0(interface_name, INTERFACE_NAME) == 0) {
        if (g_strcmp0(method_name, "GetEvents") == 0) {
            const gchar *pdata;
            g_variant_get(parameters, "(&s)", &pdata);
            (void) mp_EventsService->GetEvents(pdata, result);
        } else if (g_strcmp0(method_name, "CustomCommand") == 0) {
            const gchar *pdata;
            g_variant_get(parameters, "(&s)", &pdata);
            (void) mp_EventsService->CustomCommand(pdata, result);
        } else {

        }
    }
    gchar *response = g_strdup_printf("%s", result.c_str());
    g_dbus_method_invocation_return_value (invocation, g_variant_new("(s)", response));
    g_free (response);
}

GVariant *
EventsServiceStub::handle_get_property (GDBusConnection  *connection,
                                          const gchar *sender, const gchar *object_path,
                                          const gchar *interface_name, const gchar *property_name,
                                          GError **error, gpointer user_data) {
    GVariant *ret = nullptr;
    syslog(LOG_DEBUG, "handle_get_property: object_path=%s, property_name=%s\n", interface_name, property_name);
    if (g_strcmp0(interface_name, INTERFACE_NAME) == 0) {
        if (g_strcmp0 (property_name, "Version") == 0) {
            std::string str;
            (void)mp_EventsService->GetAPIVersion(str);
            ret = g_variant_new_string (str.c_str());
        }
    } else {}

    return ret;
}

gboolean EventsServiceStub::handle_set_property (GDBusConnection *connection, const gchar *sender,
                                                   const gchar *object_path, const gchar *interface_name,
                                                   const gchar *property_name, GVariant *value,
                                                   GError **error, gpointer user_data) {
    syslog(LOG_DEBUG, "handle_set_property\n");
    return *error == NULL;
}

void EventsServiceStub::on_bus_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    guint registration_id;
    syslog(LOG_DEBUG, "on_bus_acquired: %s\n", name);
    if (introspection_data == NULL || introspection_data->interfaces == NULL) {
        syslog(LOG_ERR, "on_bus_acquired: introspection data error\n");
        return;
    }

    static const GDBusInterfaceVTable interface_vtable = { handle_method_call, handle_get_property, handle_set_property };

    registration_id = g_dbus_connection_register_object (connection,
                                                         OBJECT_PATH,
                                                         introspection_data->interfaces[0],
                                                         &interface_vtable,
                                                         NULL,  /* user_data */
                                                         NULL,  /* user_data_free_func */
                                                         NULL); /* GError** */
    g_assert (registration_id > 0);

    sp_GDBusConnection = connection;
}

void EventsServiceStub::on_name_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    syslog(LOG_DEBUG, "on_name_acquired:\n");
}

void EventsServiceStub::on_name_lost (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    syslog(LOG_DEBUG, "on_name_lost:\n");
    exit (1);
}

//==============================================
EventsServiceStub::EventsServiceStub(IEventsService *pIEventsService){
    mp_EventsService = pIEventsService;
    if (nullptr != mp_EventsService) {
        mp_EventsService->SetListener(this);
    }
}

EventsServiceStub::~EventsServiceStub(){

}

int EventsServiceStub::Init() {
    introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
    g_assert (introspection_data != NULL);
    g_assert (introspection_data->interfaces != NULL);

    owner_id = g_bus_own_name (G_BUS_TYPE_SYSTEM,
                               BUS_NAME,
                               G_BUS_NAME_OWNER_FLAGS_REPLACE,
                               on_bus_acquired,
                               on_name_acquired,
                               on_name_lost,
                               NULL,
                               NULL);

    loop = g_main_loop_new (NULL, FALSE);
    if (loop != nullptr) {
        g_main_loop_run(loop);
        g_free(loop);
        loop = nullptr;
    }
    return 0;
}

int EventsServiceStub::Deinit() {
    if (owner_id!=0) {
        g_bus_unown_name(owner_id);
        owner_id = 0;
    }

    if (sp_GDBusConnection) {
        g_object_unref(sp_GDBusConnection);
    }

    if (nullptr != loop) {
        g_main_loop_quit(loop);
    }

    return 0;
}

bool EventsServiceStub::IsReady() {
    return sp_GDBusConnection != nullptr;
}

int EventsServiceStub::onDataStorageEvent(string value){
    GError* pError = NULL;
    g_dbus_connection_emit_signal (sp_GDBusConnection, NULL, OBJECT_PATH, INTERFACE_NAME,
                                   "onDataStorageEvent", g_variant_new ("(s)", value.c_str()), &pError);
    if (pError == nullptr) {
        return 0;
    } else {
        syslog(LOG_ERR, "client onDataStorageEvent: Failed to send message Reason: %s.\n", pError->message);
        return -1;
    }
}

int EventsServiceStub::onCustomEvent(string value){
    GError* pError = NULL;
    g_dbus_connection_emit_signal (sp_GDBusConnection, NULL, OBJECT_PATH, INTERFACE_NAME,
                                   "onCustomEvent", g_variant_new ("(s)", value.c_str()), &pError);
    if (pError == nullptr) {
        return 0;
    } else {
        syslog(LOG_ERR, "client onCustomEvent: Failed to send message Reason: %s.\n", pError->message);
        return -1;
    }
}


int EventsServiceStub::Interrupt(int cmd){
    if (cmd == 1) {
        if (nullptr != loop) {
            g_main_loop_quit(loop);
            g_main_loop_unref(loop);
            loop = nullptr;
        }
    } else {

    }
    return 0;
}