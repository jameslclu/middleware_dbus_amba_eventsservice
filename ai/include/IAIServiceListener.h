
#if !defined(MIDDLEWARE_IAISERVICE_LISTENER_H_)
#define MIDDLEWARE_IAISERVICE_LISTENER_H_
#include <string>

class IAIServiceListener
{

public:
	IAIServiceListener() {

	}

	virtual ~IAIServiceListener() {

	}

	virtual int onAIEvent(std::string const& value) =0;
    virtual int onAIModelUpdateStatusChanged(std::string const& value) =0;
    virtual int onCustomAISignal(std::string const& value) =0;
};
#endif // !defined(MIDDLEWARE_IAISERVICE_LISTENER_H_)
