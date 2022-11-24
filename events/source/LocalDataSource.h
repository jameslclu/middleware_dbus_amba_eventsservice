///////////////////////////////////////////////////////////
//  LocalDataSource.h
//  Implementation of the Class LocalDataSource
//  Created on:      24-十一月-2022 下午 04:59:54
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_B432496C_9641_4e40_86AD_FB401D00E77B__INCLUDED_)
#define EA_B432496C_9641_4e40_86AD_FB401D00E77B__INCLUDED_

#include "IEventsDataSource.h"

class LocalDataSource : public IEventsDataSource
{

public:
	LocalDataSource();
	virtual ~LocalDataSource();
	int SaveEvent();
	int GetEvents();
	int DeleteAllEvents();
	int DeleteEvent();

};
#endif // !defined(EA_B432496C_9641_4e40_86AD_FB401D00E77B__INCLUDED_)
