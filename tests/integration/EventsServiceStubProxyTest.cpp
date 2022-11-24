//
// Created by bms on 2022/11/24.
//
#include <thread>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IEventsService.h"
#include "EventsServiceStub.h"
#include "EventsServiceProxy.h"

class FakeEventsService: public IEventsService {
public:
    IEventsServiceListener* mp_Listener;

    virtual int Init() { return 0; }
    virtual int Deinit() { return 0; }
    virtual bool IsReady() { return true; }
    virtual int SetListener(IEventsServiceListener* plistener) {
        mp_Listener = plistener;
    }

    virtual int CustomCommand(string const& value, string &result) {
        result = value;
        return 0;
    }

    virtual int GetEvents(string const& value, string &result) {
        result = value;
        return 0;
    }

    virtual int GetAPIVersion(std::string &result) {
        result = "GetAPIVersion";
        return 0;
    }

    void TriggeronDataStorageEvent() {
        mp_Listener->onDataStorageEvent("onDataStorageEvent");
    }

    void TriggeronCustomEvent() {
        mp_Listener->onCustomEvent("onCustomEvent");
    }
};

static FakeEventsService s_FakeService;
static EventsServiceStub *sp_ServiceStub;
static EventsServiceProxy s_ServiceProxy;

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

class ProxyListener: public IEventsServiceListener {
public:
    string m_onDataStorageEvent;
    int onDataStorageEvent(string value) {
        m_onDataStorageEvent = value;
        return 0;
    }

    string m_onCustomEvent;
    virtual int onCustomEvent(string value) {
        m_onCustomEvent = value;
        return 0;
    }
};
static ProxyListener s_ProxyListener;
class EventsServiceStubProxyTest:public ::testing::Test {
public:
    static void SetUpTestSuite() {
        s_FakeService.Init();
        sp_ServiceStub = new EventsServiceStub(&s_FakeService);

        thread_create();
        while(!sp_ServiceStub->IsReady());

        s_ServiceProxy.Init();
        s_ServiceProxy.SetListener(&s_ProxyListener);

        while(!s_ServiceProxy.IsReady());
    }

    static void TearDownTestSuite() {
        s_FakeService.Deinit();

        sp_ServiceStub->Deinit();
        delete(sp_ServiceStub);
        sp_ServiceStub = nullptr;

        s_ServiceProxy.Deinit();
    }
};

TEST_F(EventsServiceStubProxyTest, GetEvents) {
    while(!s_ServiceProxy.IsReady());

    std::string result;
    s_ServiceProxy.GetEvents("GetEvents", result);
    std::this_thread::sleep_for(std::chrono::seconds (1));
    EXPECT_EQ("GetEvents", result);
}

TEST_F(EventsServiceStubProxyTest, CustomCommand) {
    while(!s_ServiceProxy.IsReady());

    std::string result;
    s_ServiceProxy.CustomCommand("CustomCommand", result);
    std::this_thread::sleep_for(std::chrono::seconds (1));
    EXPECT_EQ("CustomCommand", result);
}

TEST_F(EventsServiceStubProxyTest, GetAPIVersion) {
    while(!s_ServiceProxy.IsReady());

    std::string result;
    s_ServiceProxy.GetAPIVersion(result);
    std::this_thread::sleep_for(std::chrono::seconds (1));
    EXPECT_EQ("GetAPIVersion", result);
}

TEST_F(EventsServiceStubProxyTest, onCustomEvent) {
    while(!s_ServiceProxy.IsReady());

    s_FakeService.TriggeronCustomEvent();
    std::this_thread::sleep_for(std::chrono::seconds (5));
    EXPECT_EQ("onCustomEvent", s_ProxyListener.m_onCustomEvent);
}

TEST_F(EventsServiceStubProxyTest, onDataStorageEvent) {
    while(!s_ServiceProxy.IsReady());

    s_FakeService.TriggeronDataStorageEvent();
    std::this_thread::sleep_for(std::chrono::seconds (5));
    EXPECT_EQ("onDataStorageEvent", s_ProxyListener.m_onDataStorageEvent);
}