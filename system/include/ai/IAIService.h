#if !defined(MIDDLEWARE_IAISERVICE_H_)
#define MIDDLEWARE_IAISERVICE_H_
#include <string>
#include "IAIServiceListener.h"

class IAIService
{

public:
	IAIService() {

	}

	virtual ~IAIService() {

	}

	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;
    virtual int SetListener(IAIServiceListener* plistener) = 0;
	virtual int GetAIModelInfo(std::string &result) =0;
	virtual int UpdateAIModel(std::string const& value, std::string &result) =0;
    virtual int GetModelUpdateStatus(std::string &result) =0;
	virtual int SetAIConfig(std::string const& value, std::string &result) =0;
	virtual int GetAIConfig(std::string &result) =0;
	virtual int GetAPIVersion(std::string &result) =0;
    virtual int CustomCommand(std::string const& str, std::string &result) =0;
};
#endif // !defined(MIDDLEWARE_IAISERVICE_H_)
