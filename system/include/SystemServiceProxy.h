#if !defined(MIDDLEWARE_SYSTEMSERVICE_PROXY_H_)
#define MIDDLEWARE_SYSTEMSERVICE_PROXY_H_

#include "MISCServiceProxy.h"
#include "controller/ControllerServiceProxy.h"
#include "battery/BatteryServiceProxy.h"
#include "storage/StorageServiceProxy.h"

class SystemServiceProxy
{

public:
	SystemServiceProxy();
	virtual ~SystemServiceProxy();
	ControllerServiceProxy *mp_ControllerServiceProxy;
	MISCServiceProxy *mp_MISCServiceProxy;
    BatteryServiceProxy *mp_BatteryServiceProxy;
	StorageServiceProxy *mp_StorageServiceProxy;

	int Init();
	int Deinit();
	bool IsReady();
	IMISCService* GetMISCService();
	IStorageService* GetStorageService();
    IControllerService* GetControllerService();
    IBatteryService* GetBatteryService();

};
#endif // !defined(MIDDLEWARE_SYSTEMSERVICE_PROXY_H_)
