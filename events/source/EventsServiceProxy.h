///////////////////////////////////////////////////////////
//  EventsServiceProxy.h
//  Implementation of the Class EventsServiceProxy
//  Created on:      24-十一月-2022 下午 04:03:34
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_07B02669_60BA_4e92_B0EC_7AA306170B5F__INCLUDED_)
#define EA_07B02669_60BA_4e92_B0EC_7AA306170B5F__INCLUDED_

#include "IEventsServiceListener.h"
#include "IEventsService.h"

class EventsServiceProxy : public IEventsService
{

public:
	EventsServiceProxy();
	virtual ~EventsServiceProxy();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
	virtual int SetListener(IEventsServiceListener* plistener);
    virtual int CustomCommand(string const& value, string &result);
	virtual int GetEvents(string const& value, string &result);
    virtual int GetAPIVersion(string &result);
protected:
    static void* innerThread(void *arg);
    static int InvokeSetMethod(std::string const& name, std::string const& str, std::string& result);
    static int InvokeGetMethod(std::string const& name, std::string& result);
    pthread_t m_thread_tid;
    bool m_IsReady;
    bool m_IsDbusConnected = false;
    bool m_ThreadExit = false;
};
#endif // !defined(EA_07B02669_60BA_4e92_B0EC_7AA306170B5F__INCLUDED_)
