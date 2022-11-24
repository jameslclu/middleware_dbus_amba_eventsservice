#ifndef FXN_MIDDLEWARE_BATTERYSERVICEPROXY_H
#define FXN_MIDDLEWARE_BATTERYSERVICEPROXY_H

#include "IBatteryService.h"

class BatteryServiceProxy: public IBatteryService {

public:

    BatteryServiceProxy();
    ~BatteryServiceProxy();
    virtual int Init();
    virtual int Deinit();
    virtual bool IsReady();
    virtual int GetBatteryCapacity(std::string& result);
    virtual int GetAPIVersion(std::string& result);
    virtual int SetListener(IBatteryServiceListener* plistener);
    virtual int CustomCommand(std::string const& str, std::string &result);

private:
    static int InvokeSetMethod(std::string const& name, std::string const& str, std::string& result);
    static int InvokeGetMethod(std::string const& name, std::string& result);
    static void* innerThread(void *arg);
    pthread_t m_thread_tid;
    bool m_IsReady;
    bool m_IsDbusConnected = false;
    bool m_ThreadExit = false;
};

#endif //FXN_MIDDLEWARE_BATTERYSERVICEPROXY_H
