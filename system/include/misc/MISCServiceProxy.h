#if !defined(MIDDLEWARE_MISCSERIVICE_PROXY_H_)
#define MIDDLEWARE_MISCSERIVICE_PROXY_H_

#include "IMISCService.h"

class MISCServiceProxy : public IMISCService
{

public:
    MISCServiceProxy();
	virtual ~MISCServiceProxy();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
	virtual int SetListener(IMISCServiceListener* plistener);
	virtual int SetTimeZone(std::string const& value, std::string& result);
	virtual int GetTimeZone(std::string& result);
	virtual int SetTime(std::string const& value, std::string& result);
	virtual int GetTime(std::string& result);
	virtual int FactoryReset(std::string const& str, std::string& result);
	virtual int Reboot(std::string& result);
	virtual int GetSerialNumber(std::string& result);
	virtual int GetFirmwareVersion(std::string& result);
	virtual int GetHostName(std::string& result);
	virtual int SetHostName(std::string const& value, std::string& result);
	virtual int GetNetworkTimeProtocolState(std::string& result);
	virtual int SetNetworkTimeProtocolState(std::string const& value, std::string& result);
	virtual int SetPIRSensitivity(std::string const& value, std::string& result);
	virtual int GetPIRSensitivity(std::string& result);
	virtual int SetChimeType(std::string const& value, std::string& result);
	virtual int GetChimeType(std::string& result);
	virtual int GetLightSensorLevel(std::string& result);
	virtual int GetTotalInternalFlashVolume(std::string& result);
	virtual int GetFreeInternalFlashVolume(std::string& result);
	virtual int GetAPIVersion(std::string& result);

    virtual int GetBatteryVoltage(std::string &result);
    virtual int CustomCommand(std::string const& str, std::string &result);
private:
    static void* innerThread(void *arg);
    static int InvokeSetMethod(std::string const& name, std::string const& str, std::string& result);
    static int InvokeGetMethod(std::string const& name, std::string& result);
    pthread_t m_thread_tid;
    bool m_IsReady;
    bool m_IsDbusConnected = false;
    bool m_ThreadExit = false;
};
#endif // !defined(EA_17AB500B_0056_46a5_BA4C_582DABAC4737__INCLUDED_)
