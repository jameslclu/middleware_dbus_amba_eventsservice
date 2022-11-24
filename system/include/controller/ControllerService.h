
#if !defined(EA_6EABF5E5_7984_4d16_82D2_02F21E1482E2__INCLUDED_)
#define EA_6EABF5E5_7984_4d16_82D2_02F21E1482E2__INCLUDED_

#include "IControllerService.h"

class ControllerService : public IControllerService
{

public:
	ControllerService();
	virtual ~ControllerService();

    virtual int Init();
    virtual int Deinit();
    virtual bool IsReady();
    virtual int SetListener(IControllerServiceListener* plistener);
    virtual int SetLed(const std::string& value, std::string& result);
    virtual int GetLed(std::string& result);
    virtual int SetSirenState(const std::string& value, std::string& result);
    virtual int GetSirenState(std::string& result);
    virtual int GetInternalHeaterState(std::string& result);
    virtual int SetInternalHeaterState(std::string const& str, std::string& result);
    virtual int GetInternalTemperature(std::string& result);
    virtual int GetAPIVersion(std::string& result);
    virtual int CustomCommand(std::string const& str, std::string &result);
private:

};
#endif // !defined(EA_6EABF5E5_7984_4d16_82D2_02F21E1482E2__INCLUDED_)
