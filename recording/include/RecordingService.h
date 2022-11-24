#if !defined(FXN_MIDDLEWARE_RECORDINGSERVICE_H)
#define FXN_MIDDLEWARE_RECORDINGSERVICE_H

#include "IRecordingService.h"
#include "IRecordingServiceListener.h"
#include "IStorageService.h"
#include "IMISCService.h"
#include "IAIService.h"

#define RECORDING_API_VERSION "0.0.1"

class RecordingService : public IRecordingService, public IMISCServiceListener, public IStorageServiceListener, public IAIServiceListener
{

public:

	RecordingService(IMISCService* pmiscservice, IStorageService* pstorageservice, IAIService* paiservice);
	virtual ~RecordingService();

	int Init();
	int Deinit();
	bool IsReady();

	virtual int SetListener(IRecordingServiceListener* plistener);
	virtual int SetConfig(std::string const& str, std::string& result);
	virtual int GetConfig(std::string& result);
	virtual int GetAPIVersion(std::string &result);

    virtual int onPIRStateChanged(std::string const& value);
    virtual int onLightSensorLevelChanged(std::string const& value);
    virtual int onCustomMiscSignal(std::string const& value);

    virtual int onStorageFullWarning(std::string const& value);
    virtual int onFormatResult(std::string const& value);
    virtual int onCustomStorageSignal(std::string const& value);

    virtual int onAIEvent(std::string const& value);
    virtual int onCustomAISignal(std::string const& value);
    virtual int onAIModelUpdateStatusChanged(std::string const& value);

private:
    IMISCService* mp_IMISCService;
    IStorageService* mp_IStorageService;
    IAIService* mp_IAIService;
	IRecordingServiceListener* mp_IRecordingServiceListener;
    int GetSDcardResponseWhenFull(void);
};
#endif 