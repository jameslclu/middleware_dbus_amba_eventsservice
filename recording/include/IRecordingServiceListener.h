#if !defined(FXN_MIDDLEWARE_RECORDINGSERVICELISTNER_H)
#define FXN_MIDDLEWARE_RECORDINGSERVICELISTNER_H

#include <string>

class IRecordingServiceListener
{
public:

	virtual int onRecordingEvent(std::string const& str) =0;

};
#endif // !defined(EA_1C4BED05_016A_4177_9BF4_29B689458BB7__INCLUDED_)
