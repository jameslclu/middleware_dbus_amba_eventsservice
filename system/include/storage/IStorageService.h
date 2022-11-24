#if !defined(MIDDLEWARE_ISTORAGESERVICE_H_)
#define MIDDLEWARE_ISTORAGESERVICE_H_

#include <string>
#include "IStorageServiceListener.h"

class IStorageService
{

public:
	IStorageService() {

	}

	virtual ~IStorageService() {

	}

	virtual int Init() =0;
	virtual int Deinit() =0;
	virtual bool IsReady() =0;
    virtual int SetListener(IStorageServiceListener* plistener) =0;
	virtual int FormatSDCard(std::string const &str, std::string &result) =0;
	virtual int GetFileList(std::string const& str, std::string &result) =0;
	virtual int SetResponseWhenFull(std::string const& str, std::string &result) =0;
	virtual int GetResponseWhenFull(std::string &result) =0;
	virtual int GetAPIVersion(std::string &result) =0;
    virtual int CustomCommand(std::string const& str, std::string &result) =0;
};
#endif // !defined(MIDDLEWARE_ISTORAGESERVICE_H_)
