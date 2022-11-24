///////////////////////////////////////////////////////////
//  IEventsService.h
//  Implementation of the Interface IEventsService
//  Created on:      24-十一月-2022 下午 04:03:38
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_B07D7CD3_EBB3_40a1_9D3B_3182A671A7D0__INCLUDED_)
#define EA_B07D7CD3_EBB3_40a1_9D3B_3182A671A7D0__INCLUDED_

#include "IEventsServiceListener.h"

class IEventsService
{

public:
	IEventsService() {

	}

	virtual ~IEventsService() {

	}

	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;
	virtual int SetListener(IEventsServiceListener* plistener) =0;
    virtual int CustomCommand(string const& value, string &result) =0;
    virtual int GetEvents(string const& value, string &result) =0;
    virtual int GetAPIVersion(string &result) =0;
};
#endif // !defined(EA_B07D7CD3_EBB3_40a1_9D3B_3182A671A7D0__INCLUDED_)
