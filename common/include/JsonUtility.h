#ifndef FXN_MIDDLEWARE_JSONRESULTUTILITY_H
#define FXN_MIDDLEWARE_JSONRESULTUTILITY_H
#include <string>
#include <vector>
#include "ResultType.h"
#include <json/json.h>

class JsonUtility {
public:
    static std::string JsonToString(Json::Value const& value);
    static std::string ResultToJsonString(ResultType result);
    static std::string ResultToJsonString(ResultType result, int value);
    static std::string ResultToJsonString(ResultType result, std::string const& value);
    static std::string ResultToJsonString(ResultType result, std::string const& key, int value);
    static std::string ResultToJsonString(ResultType result, std::string const& key, std::string const& value);
    static std::string CMDToJsonString(std::string const& key, std::string const& value);
    static ResultType JsonStringToResult(std::string const& str);
    static ResultType JsonStringToResult(std::string const& str, std::string const& key, std::string& value);
    static std::string ParseJsonFormatToCString(std::string const& str, std::string const& key);
    static uint32_t ParseJsonFormatToUInt(std::string str, std::string const& key);
    static std::vector<uint32_t> ParseJsonFormatToUIntArray(std::string str, std::string const& key);
};

#endif //FXN_MIDDLEWARE_JSONRESULTUTILITY_H