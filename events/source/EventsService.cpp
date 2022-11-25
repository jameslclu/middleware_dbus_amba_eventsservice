///////////////////////////////////////////////////////////
//  EventsService.cpp
//  Implementation of the Class EventsService
//  Created on:      24-十一月-2022 下午 04:03:33
//  Original author: bms
///////////////////////////////////////////////////////////

#include "EventsService.h"


EventsService::EventsService(EventsRepository* pEventsRepository) {
    mp_EventsRepository = pEventsRepository;
}

EventsService::~EventsService(){

}

int EventsService::Init(){

	return 0;
}

int EventsService::Deinit(){

	return 0;
}

bool EventsService::IsReady(){
	return true;
}

int EventsService::GetAPIVersion(string &result) {
    result = "GetAPIVersion";
    return 0;
}

int EventsService::SetListener(IEventsServiceListener* plistener){
	return 0;
}

int EventsService::CustomCommand(string const& value, string &result) {
    result = "CustomCommand";
	return 0;
}

int EventsService::GetEvents(string const& value, string &result){
    result = "GetEvents";
	return 0;
}


int EventsService::onRecordingEvent(const std::string& str){

	return 0;
}


int EventsService::onAIEvent(std::string const& value){

	return 0;
}


int EventsService::onAIModelUpdateStatusChanged(std::string const& value){

	return 0;
}


int EventsService::onCustomAISignal(std::string const& value){

	return 0;
}