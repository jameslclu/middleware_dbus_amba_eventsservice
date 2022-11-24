#if !defined(MIDDLEWARE_MISCSERIVICE_LISTENER_H_)
#define MIDDLEWARE_MISCSERIVICE_LISTENER_H_
#include <string>
class IMISCServiceListener
{

public:
	IMISCServiceListener() {

	}

	virtual ~IMISCServiceListener() {

	}

    virtual int onPIRStateChanged(std::string const& value) =0;
    virtual int onLightSensorLevelChanged(std::string const& value) =0;
    virtual int onCustomMiscSignal(std::string const& value) =0;
};
#endif // !defined(MIDDLEWARE_MISCSERIVICE_LISTENER_PROXY_H_)
