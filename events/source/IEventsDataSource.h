///////////////////////////////////////////////////////////
//  IEventsDataSource.h
//  Implementation of the Interface IEventsDataSource
//  Created on:      24-十一月-2022 下午 04:03:36
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_D5EE9566_FAF3_4ff8_9011_F2EE2512880E__INCLUDED_)
#define EA_D5EE9566_FAF3_4ff8_9011_F2EE2512880E__INCLUDED_

class IEventsDataSource
{

public:
	IEventsDataSource() {

	}

	virtual ~IEventsDataSource() {

	}

	virtual int SaveEvent() =0;
	virtual int GetEvents() =0;
	virtual int DeleteAllEvents() =0;
	virtual int DeleteEvent() =0;

};
#endif // !defined(EA_D5EE9566_FAF3_4ff8_9011_F2EE2512880E__INCLUDED_)
