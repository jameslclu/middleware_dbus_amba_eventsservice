///////////////////////////////////////////////////////////
//  IEventsServiceListener.h
//  Implementation of the Interface IEventsServiceListener
//  Created on:      24-十一月-2022 下午 04:03:39
//  Original author: bms
///////////////////////////////////////////////////////////

#if !defined(EA_2A665EC1_C4D7_4b73_B907_26EBF02C0AB1__INCLUDED_)
#define EA_2A665EC1_C4D7_4b73_B907_26EBF02C0AB1__INCLUDED_
#include <string>
using std::string;

class IEventsServiceListener
{

public:
	IEventsServiceListener() {

	}

	virtual ~IEventsServiceListener() {

	}

	virtual int onDataStorageEvent(string value) =0;
	virtual int onCustomEvent(string value) =0;

};
#endif // !defined(EA_2A665EC1_C4D7_4b73_B907_26EBF02C0AB1__INCLUDED_)
