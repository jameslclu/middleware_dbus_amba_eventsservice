///////////////////////////////////////////////////////////
//  EventsService.h
//  Implementation of the Class EventsService
//  Created on:      24-十一月-2022 下午 04:03:33
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_5031AB6C_0682_4bfd_A03A_E3D3C95F1AF6__INCLUDED_)
#define EA_5031AB6C_0682_4bfd_A03A_E3D3C95F1AF6__INCLUDED_

#include "IEventsServiceListener.h"
#include "IEventsService.h"
#include "EventsRepository.h"

class EventsService : public IEventsService
{

public:
	EventsService(EventsRepository* pEventsRepository);
	virtual ~EventsService();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
	virtual int SetListener(IEventsServiceListener* plistener);
	virtual int CustomCommand(string const& value, string &result);
	virtual int GetEvents(string const& value, string &result);
    virtual int GetAPIVersion(std::string &result);
protected:
    IEventsServiceListener *mp_IEventsServiceListener;
    EventsRepository *mp_EventsRepository;
};
#endif // !defined(EA_5031AB6C_0682_4bfd_A03A_E3D3C95F1AF6__INCLUDED_)
