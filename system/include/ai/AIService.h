#if !defined(MIDDLEWARE_AISERVICE_H_)
#define MIDDLEWARE_AISERVICE_H_

#include "IAIService.h"
#include "IControllerService.h"
#include "IMISCService.h"

class AIService : public IAIService
{

public:
	AIService(IMISCService* imiscService, IControllerService *controllerService);
	virtual ~AIService();

	virtual int Init();
	virtual int Deinit();
	virtual bool IsReady();
    virtual int SetListener(IAIServiceListener* plistener);
	virtual int GetAIModelInfo(std::string& result);
	virtual int UpdateAIModel(const std::string& value, std::string& result);
	virtual int SetAIConfig(const std::string& value, std::string& result);
	virtual int GetAIConfig(std::string& result);
	virtual int GetAPIVersion(std::string& result);
    virtual int CustomCommand(std::string const& str, std::string &result);
private:
    IAIServiceListener* mp_IAIServiceListener;
};
#endif // !defined(MIDDLEWARE_AISERVICE_H_)
