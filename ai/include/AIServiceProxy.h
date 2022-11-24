
#if !defined(MIDDLEWARE_AISERVICE_PROXY_H_)
#define MIDDLEWARE_AISERVICE_PROXY_H_

#include "IAIService.h"

class AIServiceProxy : public IAIService
{

public:
	AIServiceProxy();
	virtual ~AIServiceProxy();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
    virtual int SetListener(IAIServiceListener* plistener);
    virtual int GetAIModelInfo(std::string& result);
	virtual int UpdateAIModel(std::string const& value, std::string& result);
    virtual int GetModelUpdateStatus(std::string &result);
	virtual int SetAIConfig(std::string const& value, std::string& result);
	virtual int GetAIConfig(std::string& result);
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
#endif // !defined(MIDDLEWARE_AISERVICE_PROXY_H_)
