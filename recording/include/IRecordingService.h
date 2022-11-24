#ifndef FXN_MIDDLEWARE_IRECORDINGSERVICE_H
#define FXN_MIDDLEWARE_IRECORDINGSERVICE_H

#include <string>
#include "IRecordingServiceListener.h"

class IRecordingService
{

public:
	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;

	virtual int SetListener(IRecordingServiceListener* plistener) = 0;
	virtual int SetConfig(std::string const& str, std::string &result) =0;
	virtual int GetConfig(std::string &result) =0;
	virtual int GetAPIVersion(std::string &result) =0;

};

#endif //FXN_MIDDLEWARE_IAUDIOSERVICE_H
