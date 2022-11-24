///////////////////////////////////////////////////////////
//  EventsRepository.h
//  Implementation of the Class EventsRepository
//  Created on:      24-十一月-2022 下午 04:03:30
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_4C6BEC95_7EE1_40a2_9CD1_217F12B2C4FF__INCLUDED_)
#define EA_4C6BEC95_7EE1_40a2_9CD1_217F12B2C4FF__INCLUDED_

#include "LocalDataSource.h"
#include <string>
using std::string;
class EventsRepository
{

public:
	EventsRepository(IEventsDataSource* pEventsDataSource);
	virtual ~EventsRepository();
	LocalDataSource *m_LocalDataSource;

	int GetRecordingEvents(int type, int date);
	int GetAIEvents(int type, string date);
	int SaveAIEvent(int type, int date);
	int SaveRecordingEvent(int type, int date, int filepath);
protected:
    IEventsDataSource* mp_EventsDataSource;
};
#endif // !defined(EA_4C6BEC95_7EE1_40a2_9CD1_217F12B2C4FF__INCLUDED_)
