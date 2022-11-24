#if !defined(MIDDLEWARE_SYSTEMSERVICE_STUB_H_)
#define MIDDLEWARE_SYSTEMSERVICE_STUB_H_

#include <string>
#include <glib/gprintf.h>
#include <glib/gtypes.h>
#include <glib/gmain.h>
#include <gio/gio.h>
#include <gio/giotypes.h>
#include <gio/gdbusconnection.h>

#include "controller/IControllerService.h"
#include "controller/IControllerServiceListener.h"
#include "storage/IStorageService.h"
#include "storage/IStorageServiceListener.h"
#include "misc/IMISCService.h"
#include "misc/IMISCServiceListener.h"
#include "battery/IBatteryService.h"

class SystemServiceStub : public IControllerServiceListener, public IStorageServiceListener,
        public IMISCServiceListener, public IBatteryServiceListener
{

public:
	SystemServiceStub(IControllerService *controllerService,
                      IStorageService *storageService,
                      IMISCService *systemService,
                      IBatteryService *batteryService);

	virtual ~SystemServiceStub();

    int Init();
    int Deinit();
    bool IsReady();

    virtual int onInternalHeaterStatusChanged(std::string const& value);
    virtual int onPIRStateChanged(std::string const& value);
    virtual int onStorageFullWarning(std::string const& value);
    virtual int onFormatResult(std::string const& value);
    virtual int onInternalTemperatureChanged(std::string const& result);
    virtual int onLightSensorLevelChanged(std::string const& value);
    virtual int onLowBattery(std::string const& value);
    virtual int onCapacityChanged(std::string const& value);

    virtual int onCustomBatterySignal(std::string const& value);
    virtual int onCustomMiscSignal(std::string const& value);
    virtual int onCustomStorageSignal(std::string const& value);
    virtual int onCustomControllerSignal(std::string const& value);

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
