///////////////////////////////////////////////////////////
//  EventsServiceStub.h
//  Implementation of the Class EventsServiceStub
//  Created on:      24-十一月-2022 下午 04:03:35
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_F52F693F_B151_4194_B03A_353F79AFA39B__INCLUDED_)
#define EA_F52F693F_B151_4194_B03A_353F79AFA39B__INCLUDED_
#include <string>
#include <glib/gprintf.h>
#include <glib/gtypes.h>
#include <glib/gmain.h>
#include <gio/gio.h>
#include <gio/giotypes.h>
#include <gio/gdbusconnection.h>

#include "IEventsServiceListener.h"
#include "EventsService.h"
#include "IEventsService.h"

using std::string;

class EventsServiceStub : public IEventsServiceListener
{

public:
	EventsServiceStub(IEventsService *pIEventsService);
	virtual ~EventsServiceStub();

    int Init();
    int Deinit();
    bool IsReady();

	virtual int onDataStorageEvent(string value);
	virtual int onCustomEvent(string value);
	int Interrupt(int cmd);

protected:
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

protected:
//    static IEventsService *mp_EventsService;
//    static GMainLoop *loop;
//    static guint owner_id;
//    static GDBusConnection* sp_GDBusConnection;// = nullptr;
//    static bool s_ready;// = false;
//    static GDBusNodeInfo *introspection_data;// = nullptr;
};
#endif // !defined(EA_F52F693F_B151_4194_B03A_353F79AFA39B__INCLUDED_)
