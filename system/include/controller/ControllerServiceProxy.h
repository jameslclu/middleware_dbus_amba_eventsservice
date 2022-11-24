#if !defined(MIDDLEWARE_ICONTROLLERSERVICE_PROXY_H_)
#define MIDDLEWARE_ICONTROLLERSERVICE_PROXY_H_

#include "IControllerService.h"

class ControllerServiceProxy : public IControllerService
{

public:
	ControllerServiceProxy();
	virtual ~ControllerServiceProxy();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
    virtual int SetListener(IControllerServiceListener* plistener);
	virtual int SetLed(std::string const& value, std::string& result);
	virtual int GetLed(std::string& result);
	virtual int SetSirenState(std::string const& value, std::string& result);
	virtual int GetSirenState(std::string& result);
	virtual int GetInternalHeaterState(std::string& result);
	virtual int SetInternalHeaterState(std::string const& str, std::string& result);
	virtual int GetInternalTemperature(std::string& result);
	virtual int GetAPIVersion(std::string& result);
    virtual int CustomCommand(std::string const& str, std::string &result);
private:
    static void* innerThread(void *arg);
    static int InvokeSetMethod(std::string const& name, std::string const& str, std::string& result);
    static int InvokeGetMethod(std::string const& name, std::string& result);
    pthread_t m_thread_tid;
    bool m_IsReady;
    bool m_IsDbusConnected = false;
    bool m_ThreadExit = false;
};
#endif // !defined(MIDDLEWARE_ICONTROLLERSERVICELISTENER_H_)
