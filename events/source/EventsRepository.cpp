///////////////////////////////////////////////////////////
//  EventsRepository.cpp
//  Implementation of the Class EventsRepository
//  Created on:      24-十一月-2022 下午 04:03:30
//  Original author: bms
///////////////////////////////////////////////////////////

#include "EventsRepository.h"


EventsRepository::EventsRepository(IEventsDataSource* pEventsDataSource) {
    mp_EventsDataSource = pEventsDataSource;
}

EventsRepository::~EventsRepository(){

}


int EventsRepository::GetRecordingEvents(int type, int date){

	return 0;
}


int EventsRepository::GetAIEvents(int type, string date){

	return 0;
}


int EventsRepository::SaveAIEvent(int type, int date){

	return 0;
}


int EventsRepository::SaveRecordingEvent(int type, int date, int filepath){

	return 0;
}