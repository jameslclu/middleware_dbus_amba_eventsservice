#if !defined(MIDDLEWARE_STORAGESERVICE_H_)
#define MIDDLEWARE_STORAGESERVICE_H_

#include "IStorageService.h"

class StorageService : public IStorageService
{

public:
	StorageService();
	virtual ~StorageService();

    virtual int Init() override;
    virtual int Deinit() override;
    virtual bool IsReady() override;
    virtual int SetListener(IStorageServiceListener* plistener) override;
    virtual int FormatSDCard(std::string const &value, std::string &result) override;
    virtual int GetFileList(std::string const& value, std::string& result) override;
    virtual int SetResponseWhenFull(std::string const& value, std::string& result) override;
    virtual int GetResponseWhenFull(std::string& result) override;
    virtual int GetAPIVersion(std::string& result) override;
    virtual int CustomCommand(std::string const& str, std::string &result);
private:

};
#endif
