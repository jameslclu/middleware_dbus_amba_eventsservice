#if !defined(MIDDLEWARE_IMISCSEREVICE_H_)
#define MIDDLEWARE_IMISCSEREVICE_H_

#include <string>
#include "IMISCServiceListener.h"

class IMISCService
{

public:
	IMISCService() {

	}

	virtual ~IMISCService() {

	}

	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;
	virtual int SetListener(IMISCServiceListener* plistener) =0;
	virtual int SetTimeZone(std::string const& str, std::string &result) =0;
	virtual int GetTimeZone(std::string &result) =0;
	virtual int SetTime(std::string const& str, std::string &result) =0;
	virtual int GetTime(std::string &result) =0;
	virtual int FactoryReset(std::string const& str, std::string &result) =0;
	virtual int Reboot(std::string &result) =0;
	virtual int GetSerialNumber(std::string &result) =0;
	virtual int GetFirmwareVersion(std::string &result) =0;
	virtual int GetHostName(std::string &result) =0;
	virtual int SetHostName(std::string const& str, std::string &result) =0;
	virtual int GetNetworkTimeProtocolState(std::string &result) =0;
	virtual int SetNetworkTimeProtocolState(std::string const& str, std::string &result) =0;
	virtual int SetPIRSensitivity(std::string const& str, std::string &result) =0;
	virtual int GetPIRSensitivity(std::string& result) =0;
	virtual int SetChimeType(std::string const& str, std::string &result) =0;
	virtual int GetChimeType(std::string &result) =0;
	virtual int GetLightSensorLevel(std::string &result) =0;
    virtual int GetBatteryVoltage(std::string &result) =0;
	virtual int GetTotalInternalFlashVolume(std::string &result) =0;
	virtual int GetFreeInternalFlashVolume(std::string &result) =0;
    virtual int GetAPIVersion(std::string &result) =0;
	virtual int CustomCommand(std::string const& str, std::string &result) =0;

};
#endif // !defined(MIDDLEWARE_IMISCSERVICE_H_)
