#if !defined(MIDDLEWARE_ICONTROLLERSERVICE_H_)
#define MIDDLEWARE_ICONTROLLERSERVICE_H_

#include <string>
#include "IControllerServiceListener.h"

class IControllerService
{

public:
	IControllerService() {

	}

	virtual ~IControllerService() {

	}

	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;
    virtual int SetListener(IControllerServiceListener* plistener) = 0;
	virtual int SetLed(std::string const& value, std::string& result) = 0;
	virtual int GetLed(std::string &result) =0;
	virtual int SetSirenState(std::string const& value, std::string& result) =0;
	virtual int GetSirenState(std::string &result) =0;
	virtual int GetInternalHeaterState(std::string &result) =0;
	virtual int SetInternalHeaterState(std::string const& str, std::string &result) =0;
	virtual int GetInternalTemperature(std::string &result) =0;
	virtual int GetAPIVersion(std::string &result) =0;
    virtual int CustomCommand(std::string const& str, std::string &result) =0;
};
#endif //
