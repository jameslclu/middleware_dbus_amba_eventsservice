//
// Created by bms on 2022/11/25.
//
#include <thread>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IEventsService.h"
#include "EventsServiceStub.h"
#include "EventsServiceProxy.h"
#include "RecordingServiceStub.h"
#include "RecordingServiceProxy.h"

static RecordingServiceStub sp_recordingServiceStub(nullptr);

class HookEventsService: public EventsService {
public:
    HookEventsService(EventsRepository* pEventsRepository): EventsService(pEventsRepository) {}
    virtual ~HookEventsService() {}
    bool m_Got_OnAIEvent = false;
    string m_onAIEvent;
    virtual int onAIEvent(std::string const& value) {
        m_Got_OnAIEvent = true;
        m_onAIEvent = value;
    }

    bool m_Got_onRecordingEvent = false;
    string m_onRecordingEvent;
    virtual int onRecordingEvent(const std::string& str) {
        m_Got_onRecordingEvent = true;
        m_onRecordingEvent = str;
    }
};

static HookEventsService s_HookService(nullptr);
static EventsServiceStub *sp_ServiceStub;
static RecordingServiceProxy s_recordingServiceProxy;

static void* run(void* para)
{
    sp_ServiceStub->Init();
    return ((void*)0);
}

static int thread_create(void)
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, run, NULL);

    return err;
}

static void* run2(void* para)
{
    sp_recordingServiceStub.Init();
    return ((void*)0);
}

static int thread_create2(void)
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, run2, NULL);

    return err;
}

class EventsServiceGotRecordingEvent:public ::testing::Test {
public:
    static void SetUpTestSuite() {
        // Remote - AI Service
        //sp_aiServiceStub.Init();
        //sp_aiServiceStub.onAIEvent("onAIEvent");
        thread_create2();
        while(!sp_recordingServiceStub.IsReady());

        // s_HookService

        // Local - Event Service
        // 1. Stub
        // 2. Service
        sp_ServiceStub = new EventsServiceStub(nullptr);
        thread_create();
        while(!sp_ServiceStub->IsReady());

        s_recordingServiceProxy.Init();
        s_recordingServiceProxy.SetListener(&s_HookService);
        while(!s_recordingServiceProxy.IsReady());
    }

    static void TearDownTestSuite() {
        sp_ServiceStub->Deinit();
        delete(sp_ServiceStub);
        sp_ServiceStub = nullptr;
    }
};

TEST_F(EventsServiceGotRecordingEvent, GetEvents) {
    sp_recordingServiceStub.onRecordingEvent("onRecordingEvent");
    for (int i=0; i<20; i++) {
        std::this_thread::sleep_for(std::chrono::seconds (1));
        if (s_HookService.m_Got_onRecordingEvent == true) {
            break;
        }
    }
}