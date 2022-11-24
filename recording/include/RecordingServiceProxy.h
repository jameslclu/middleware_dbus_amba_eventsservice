#if !defined(MIDDLEWARE_RECORDINGSREVICE_PROXY_H_)
#define MIDDLEWARE_RECORDINGSREVICE_PROXY_H_

#include "IRecordingService.h"

class RecordingServiceProxy : public IRecordingService
{

public:
	RecordingServiceProxy();
	virtual ~RecordingServiceProxy();

	int Init();
	int Deinit();
	bool IsReady();

	virtual int SetListener(IRecordingServiceListener* plistener);
	virtual int SetConfig(const std::string& value, std::string& result);
	virtual int GetConfig(std::string& result);
	virtual int GetAPIVersion(std::string& result);

private:
    static void* innerThread(void *arg);
    static int InvokeSetMethod(std::string const& name, std::string const& str, std::string& result);
    static int InvokeGetMethod(std::string const& name, std::string& result);
    pthread_t m_thread_tid;
    bool m_IsReady;
    bool m_IsDbusConnected = false;
    bool m_ThreadExit = false;
};
#endif // !defined(MIDDLEWARE_RECORDINGSREVICE_PROXY_H_)
