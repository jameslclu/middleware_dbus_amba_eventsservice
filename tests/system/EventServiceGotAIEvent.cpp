//
// Created by bms on 2022/11/25.
//
#include <thread>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IEventsService.h"
#include "EventsServiceStub.h"
#include "EventsServiceProxy.h"
#include "AIServiceStub.h"
#include "AIServiceProxy.h"

static AIServiceStub sp_aiServiceStub(nullptr);

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
};

static HookEventsService s_HookService(nullptr);
static EventsServiceStub *sp_ServiceStub;
static AIServiceProxy s_aiServiceProxy;

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
    sp_aiServiceStub.Init();
    return ((void*)0);
}

static int thread_create2(void)
{
    int err;
    pthread_t thr;

    err = pthread_create(&thr, NULL, run2, NULL);

    return err;
}

class EventsServiceGotAIEvent:public ::testing::Test {
public:
    static void SetUpTestSuite() {
        // Remote - AI Service
        //sp_aiServiceStub.Init();
        //sp_aiServiceStub.onAIEvent("onAIEvent");
        thread_create2();
        while(!sp_aiServiceStub.IsReady());

        // s_HookService

        // Local - Event Service
        // 1. Stub
        // 2. Service
        sp_ServiceStub = new EventsServiceStub(nullptr);
        thread_create();
        while(!sp_ServiceStub->IsReady());

        s_aiServiceProxy.Init();
        s_aiServiceProxy.SetListener(&s_HookService);
        while(!s_aiServiceProxy.IsReady());
    }

    static void TearDownTestSuite() {
        sp_ServiceStub->Deinit();
        delete(sp_ServiceStub);
        sp_ServiceStub = nullptr;
    }
};

TEST_F(EventsServiceGotAIEvent, GetEvents) {
    sp_aiServiceStub.onAIEvent("onAIEvent");
    for (int i=0; i<20; i++) {
        std::this_thread::sleep_for(std::chrono::seconds (1));
        if (s_HookService.m_Got_OnAIEvent == true) {
            break;
        }
    }
}