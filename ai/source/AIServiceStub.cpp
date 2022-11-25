#include <unistd.h>
#include <sys/syslog.h>
#include "AIServiceStub.h"
#include "AIConfig.h"

static IAIService* sp_IAIService;

static GMainLoop *loop;
static guint owner_id;
static GDBusConnection* sp_GDBusConnection = nullptr;
static bool s_ready = false;
static GDBusNodeInfo *introspection_data = nullptr;

static const gchar introspection_xml[] = {
        "<node>"
        "  <interface name='fxn.camera.ai'>"
        "    <method name='CustomCommand'>"
        "      <arg type='s' name='value' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='GetAIModelInfo'>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='UpdateAIModel'>"
        "      <arg type='s' name='config' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='GetModelUpdateStatus'>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='SetAIConfig'>"
        "      <arg type='s' name='config' direction='in'/>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <method name='GetAIConfig'>"
        "      <arg type='s' name='response' direction='out'/>"
        "    </method>"
        "    <signal name='onAIModelUpdateStatusChanged'>"
        "      <arg type='s' name='value'/>"
        "    </signal>"
        "    <signal name='onAIEvent'>"
        "      <arg type='s' name='value'/>"
        "    </signal>"
        "    <signal name='onCustomSignal'>"
        "      <arg type='s' name='value'/>"
        "    </signal>"
        "    <property type='s' name='Version' access='read'/>"
        "  </interface>"
        "</node>"};

//========================================================================================================
void
AIServiceStub::handle_method_call (GDBusConnection       *connection,
                    const gchar           *sender,
                    const gchar           *object_path,
                    const gchar           *interface_name,
                    const gchar           *method_name,
                    GVariant              *parameters,
                    GDBusMethodInvocation *invocation,
                    gpointer               user_data) {
    syslog(LOG_DEBUG, "handle_method_call: object_path=%s, interface_name=%s\n", object_path, interface_name);

    std::string result = "invalid";
    if (g_strcmp0(interface_name, AI_INTERFACE_NAME) == 0) {
        if (g_strcmp0(method_name, "GetAIModelInfo") == 0) {
            (void) sp_IAIService->GetAIModelInfo(result);
        } else if (g_strcmp0(method_name, "UpdateAIModel") == 0) {
            const gchar *pdata;
            g_variant_get(parameters, "(&s)", &pdata);
            (void) sp_IAIService->UpdateAIModel(pdata, result);
        } else if (g_strcmp0(method_name, "GetModelUpdateStatus") == 0) {
            (void) sp_IAIService->GetModelUpdateStatus(result);
        } else if (g_strcmp0(method_name, "SetAIConfig") == 0) {
            const gchar *pdata;
            g_variant_get(parameters, "(&s)", &pdata);
            (void) sp_IAIService->SetAIConfig(pdata, result);
        } else if (g_strcmp0(method_name, "GetAIConfig")== 0) {
            (void) sp_IAIService->GetAIConfig(result);
        } else if (g_strcmp0(method_name, "CustomCommand") == 0) {
            const gchar *pdata;
            g_variant_get(parameters, "(&s)", &pdata);
            (void) sp_IAIService->CustomCommand(pdata, result);
        } else {}
    } else {
    }

    gchar *response = g_strdup_printf("%s", result.c_str());
    g_dbus_method_invocation_return_value (invocation,g_variant_new ("(s)", response));
    g_free (response);
}

int AIServiceStub::Interrupt(int cmd) {
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

GVariant *
AIServiceStub::handle_get_property (GDBusConnection  *connection,
                     const gchar *sender, const gchar *object_path,
                     const gchar *interface_name, const gchar *property_name,
                     GError **error, gpointer user_data) {
    GVariant *ret = g_variant_new_string("no");
    syslog(LOG_DEBUG, "handle_get_property: object_path=%s, property_name=%s\n", interface_name, property_name);
    if (g_strcmp0(interface_name, AI_INTERFACE_NAME) == 0) {
        if (g_strcmp0 (property_name, "Version") == 0) {
            std::string str;
            if (sp_IAIService!= nullptr) {
                (void)sp_IAIService->GetAPIVersion(str);
                ret = g_variant_new_string (str.c_str());
            }
        }
    } else { }

    return ret;
}

gboolean AIServiceStub::handle_set_property (GDBusConnection *connection, const gchar *sender,
                                     const gchar *object_path, const gchar *interface_name,
                                     const gchar *property_name, GVariant *value,
                                     GError **error, gpointer user_data) {
    syslog(LOG_DEBUG, "handle_set_property\n");
    return *error == nullptr;
}

void AIServiceStub::on_bus_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    guint registration_id;
    syslog(LOG_DEBUG, "on_bus_acquired: %s\n", name);
    if (introspection_data == nullptr || introspection_data->interfaces == nullptr) {
        syslog(LOG_ERR, "on_bus_acquired: introspection data error\n");
        return;
    }

    static const GDBusInterfaceVTable interface_vtable = { handle_method_call, handle_get_property, handle_set_property };

    registration_id = g_dbus_connection_register_object (connection,
                                                         AI_OBJECT_PATH,
                                                         introspection_data->interfaces[0],
                                                         &interface_vtable,
                                                         NULL,  /* user_data */
                                                         NULL,  /* user_data_free_func */
                                                         NULL); /* GError** */
    g_assert (registration_id > 0);


    sp_GDBusConnection = connection;
}

void AIServiceStub::on_name_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    syslog(LOG_DEBUG, "on_name_acquired:\n");
}

void AIServiceStub::on_name_lost (GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    syslog(LOG_DEBUG, "on_name_lost:\n");
    exit (1);
}

//=========================================================================================================

AIServiceStub::AIServiceStub(IAIService *iaiService) {
    sp_IAIService = iaiService;
    if (nullptr != sp_IAIService) {
        sp_IAIService->SetListener(this);
    }
}

AIServiceStub::~AIServiceStub() {

}

int AIServiceStub::Init() {
    introspection_data = g_dbus_node_info_new_for_xml (introspection_xml, NULL);
    g_assert (introspection_data != NULL);
    g_assert (introspection_data->interfaces != NULL);

    owner_id = g_bus_own_name (G_BUS_TYPE_SYSTEM,
                               AI_BUS_NAME,
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

int AIServiceStub::Deinit() {
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

bool AIServiceStub::IsReady() {
    return sp_GDBusConnection != nullptr;
}

int AIServiceStub::onAIEvent(std::string const& value){
    GError* pError = NULL;
    g_dbus_connection_emit_signal (sp_GDBusConnection, NULL, AI_OBJECT_PATH, AI_INTERFACE_NAME,
                                   "onAIEvent", g_variant_new ("(s)", value.c_str()), &pError);
    if (pError == nullptr) {
        return 0;
    } else {
        syslog(LOG_ERR, "client onAIEvent: Failed to send message Reason: %s.\n", pError->message);
        return -1;
    }
}

int AIServiceStub::onAIModelUpdateStatusChanged(std::string const& value) {
    GError* pError = NULL;
    g_dbus_connection_emit_signal(sp_GDBusConnection, NULL, AI_OBJECT_PATH, AI_INTERFACE_NAME,
                                   "onAIModelUpdateStatusChanged", g_variant_new ("(s)", value.c_str()), &pError);
    if (pError == nullptr) {
        return 0;
    } else {
        syslog(LOG_ERR, "client onAIModelUpdateStatusChanged: Failed to send message Reason: %s.\n", pError->message);
        return -1;
    }
}

int AIServiceStub::onCustomAISignal(std::string const& value) {
    GError* pError = NULL;
    g_dbus_connection_emit_signal (sp_GDBusConnection, NULL, AI_OBJECT_PATH, AI_INTERFACE_NAME,
                                   "onCustomAISignal", g_variant_new ("(s)", value.c_str()), &pError);
    if (pError == nullptr) {
        return 0;
    } else {
        syslog(LOG_ERR, "client onCustomAISignal: Failed to send message Reason: %s.\n", pError->message);
        return -1;
    }
}