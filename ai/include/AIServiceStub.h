#if !defined(MIDDLEWARE_AISERVICE_STUB_H_)
#define MIDDLEWARE_AISERVICE_STUB_H_

#include <string>
#include <glib/gprintf.h>
#include <glib/gtypes.h>
#include <glib/gmain.h>
#include <gio/gio.h>
#include <gio/giotypes.h>
#include <gio/gdbusconnection.h>

#include "IAIService.h"
#include "IAIServiceListener.h"

class AIServiceStub : public IAIServiceListener
{

public:
    AIServiceStub(IAIService *aiService);

	virtual ~AIServiceStub();

    int Init();
    int Deinit();
    bool IsReady();

    int Interrupt(int cmd);

    virtual int onAIEvent(std::string const& value);
    virtual int onCustomAISignal(std::string const& value);
    virtual int onAIModelUpdateStatusChanged(std::string const& value);

private:
    static void on_bus_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data);
    static void on_name_acquired (GDBusConnection *connection, const gchar *name, gpointer user_data);
    static void on_name_lost (GDBusConnection *connection, const gchar *name, gpointer user_data);

    static void
    handle_method_call (GDBusConnection       *connection,
                        const gchar           *sender,
                        const gchar           *object_path,
                        const gchar           *interface_name,
                        const gchar           *method_name,
                        GVariant              *parameters,
                        GDBusMethodInvocation *invocation,
                        gpointer               user_data);

    static GVariant *
    handle_get_property (GDBusConnection  *connection,
                         const gchar *sender, const gchar *object_path,
                         const gchar *interface_name, const gchar *property_name,
                         GError **error, gpointer user_data);

    static gboolean handle_set_property (GDBusConnection *connection, const gchar *sender,
                                         const gchar *object_path, const gchar *interface_name,
                                         const gchar *property_name, GVariant *value,
                                         GError **error, gpointer user_data);

};
#endif // !defined(MIDDLEWARE_SYSTEMSERVICE_STUB_H_)
