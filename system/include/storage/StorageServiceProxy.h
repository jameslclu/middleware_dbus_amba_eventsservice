

#if !defined(MIDDLEWARE_STORAGESERVICE_PROXY_H_)
#define MIDDLEWARE_STORAGESERVICE_PROXY_H_

#include "IStorageService.h"

class StorageServiceProxy : public IStorageService
{

public:
	StorageServiceProxy();
	virtual ~StorageServiceProxy();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
    virtual int SetListener(IStorageServiceListener* plistener);
	virtual int FormatSDCard(std::string const& value, std::string& result);
	virtual int GetFileList(std::string const& value, std::string& result);
	virtual int SetResponseWhenFull(std::string const& value, std::string& result);
	virtual int GetResponseWhenFull(std::string& result);
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
#endif // !defined(MIDDLEWARE_STORAGESERVICE_PROXY_H_)
