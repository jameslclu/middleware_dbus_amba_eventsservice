#ifndef FXN_MIDDLEWARE_BATTERYSERVICE_H
#define FXN_MIDDLEWARE_BATTERYSERVICE_H

#include "IBatteryService.h"

#define BATTERY_API_VERSION "0.0.1"
#define BATTERY_LOOP_SLEEP_SECOND 5

class BatteryService: public IBatteryService {
public:
    BatteryService();
    virtual ~BatteryService();

    virtual int Init();
    virtual int Deinit();
    virtual bool IsReady();
    virtual int GetBatteryCapacity(std::string &result);
    virtual int GetAPIVersion(std::string &result);
    virtual int SetListener(IBatteryServiceListener* plistener);
    virtual int CustomCommand(std::string const& str, std::string &result);
};

#endif //FXN_MIDDLEWARE_BATTERYSERVICE_H
