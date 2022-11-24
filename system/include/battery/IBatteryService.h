#ifndef FXN_MIDDLEWARE_IBATTERYSERVICE_H
#define FXN_MIDDLEWARE_IBATTERYSERVICE_H

#include <string>

class IBatteryServiceListener {
public:
    virtual int onLowBattery(std::string const& value) = 0;
    virtual int onCapacityChanged(std::string const& value) = 0;
    virtual int onCustomBatterySignal(std::string const& value) =0;
};

class IBatteryService {
public:
    virtual int Init() = 0;
    virtual int Deinit()= 0;
    virtual bool IsReady() = 0;
    virtual int GetBatteryCapacity(std::string& result)= 0;
    virtual int GetAPIVersion(std::string& result)= 0;
    virtual int SetListener(IBatteryServiceListener* plistener)= 0;
    virtual int CustomCommand(std::string const& str, std::string &result) =0;
};

#endif //FXN_MIDDLEWARE_IBATTERYSERVICE_H