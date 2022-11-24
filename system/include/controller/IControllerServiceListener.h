
#if !defined(MIDDLEWARE_ICONTROLLERSERVICELISTENER_H_)
#define MIDDLEWARE_ICONTROLLERSERVICELISTENER_H_
#include <string>
class IControllerServiceListener
{

public:
	IControllerServiceListener() {

	}

	virtual ~IControllerServiceListener() {

	}

	virtual int onInternalHeaterStatusChanged(std::string const& value) =0;
	virtual int onInternalTemperatureChanged(std::string const& value) =0;
    virtual int onCustomControllerSignal(std::string const& value) =0;

};
#endif // !defined(MIDDLEWARE_ICONTROLLERSERVICELISTENER_H_)
