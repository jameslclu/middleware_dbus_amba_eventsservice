#if !defined(MIDDLEWARE_ISTORAGESERVICELISTENER_H_)
#define MIDDLEWARE_ISTORAGESERVICELISTENER_H_

#include <string>
class IStorageServiceListener
{

public:
	IStorageServiceListener() {

	}

	virtual ~IStorageServiceListener() {

	}

	virtual int onStorageFullWarning(std::string const& value) =0;

    virtual int onFormatResult(std::string const& value) =0;

    virtual int onCustomStorageSignal(std::string const& value) =0;
};
#endif // !defined(MIDDLEWARE_ISTORAGESERVICELISTENER_H_)
