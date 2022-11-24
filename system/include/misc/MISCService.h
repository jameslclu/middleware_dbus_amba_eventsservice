#if !defined(MIDDLEWARE_MISCSERIVICE_H_)
#define MIDDLEWARE_MISCSERIVICE_H_

#include "IMISCService.h"
#include "IMISCServiceListener.h"

class MISCService : public IMISCService
{

public:
	MISCService();
	virtual ~MISCService();

    virtual int Init();
    virtual int Deinit();
    virtual bool IsReady();
    virtual int SetListener(IMISCServiceListener* plistener);
    virtual int SetTimeZone(const std::string& str, std::string& result);
    virtual int GetTimeZone(std::string& result);
    virtual int SetTime(const std::string& str, std::string& result);
    virtual int GetTime(std::string& result);
    virtual int FactoryReset(std::string const& str, std::string& result);
    virtual int Reboot(std::string& result);
    virtual int GetSerialNumber(std::string& result);
    virtual int GetFirmwareVersion(std::string& result);
    virtual int GetHostName(std::string& result);
    virtual int SetHostName(const std::string& str, std::string& result);
    virtual int GetNetworkTimeProtocolState(std::string& result);
    virtual int SetNetworkTimeProtocolState(const std::string& str, std::string& result);
    virtual int SetPIRSensitivity(const std::string& str, std::string& result);
    virtual int GetPIRSensitivity(std::string& result);
    virtual int SetChimeType(const std::string& str, std::string& result);
    virtual int GetChimeType(std::string& result);
    virtual int GetLightSensorLevel(std::string& result);
    virtual int GetTotalInternalFlashVolume(std::string& result);
    virtual int GetFreeInternalFlashVolume(std::string& result);
    virtual int GetBatteryVoltage(std::string &result);
    virtual int GetAPIVersion(std::string& result);
    virtual int CustomCommand(std::string const& str, std::string &result);
private:

};
#endif // !defined(MIDDLEWARE_MISCSERIVICE_PROXY_H_)
