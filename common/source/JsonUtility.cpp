

#include "JsonUtility.h"

std::string JsonUtility::JsonToString(Json::Value const& value) {
    Json::Value obj;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    return Json::writeString(builder, value);
}

std::string JsonUtility::ResultToJsonString(ResultType result) {
    Json::Value obj;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";

    switch(result) {
        case ResultType::OK:
            obj["result"] = Json::Value("OK");
            return Json::writeString(builder, obj);
        case ResultType::ERROR:
            obj["result"] = Json::Value("Error");
            return Json::writeString(builder, obj);
        case ResultType::ERROR_BUSY:
            obj["result"] = Json::Value("Error-busy");
            return Json::writeString(builder, obj);
        case ResultType::ERROR_INVALID_JSON_FORMAT:
            obj["result"] = Json::Value("Error-InvalidJsonFormat");
            return Json::writeString(builder, obj);
        case ResultType::ERROR_INVALID_INPUT:
            obj["result"] = Json::Value("Error-InvalidInput");
            return Json::writeString(builder, obj);
        case ResultType::ERROR_OUT_OF_RANGE:
            obj["result"] = Json::Value("Error-OutOfRange");
            return Json::writeString(builder, obj);
        default:
            return "";
    }
}

std::string JsonUtility::ResultToJsonString(ResultType result, int value) {
    return JsonUtility::ResultToJsonString(result, "value", value);
}

std::string JsonUtility::ResultToJsonString(ResultType result, std::string const& value) {
    return JsonUtility::ResultToJsonString(result, "value", value);
}

std::string JsonUtility::ResultToJsonString(ResultType result, std::string const& key, int value) {
    Json::Value obj;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    switch(result) {
        case ResultType::OK:
            obj["result"] = Json::Value("OK");
            obj[key] =  Json::Value(value);
            return Json::writeString(builder, obj);
        case ResultType::ERROR:
            obj["result"] = Json::Value("Error");
            obj[key] =  Json::Value(value);
            return Json::writeString(builder, obj);
        default:
            return "";
    }
}

std::string JsonUtility::ResultToJsonString(ResultType result, std::string const& key, std::string const& value) {
    Json::Value obj;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    switch(result) {
        case ResultType::OK:
            obj["result"] = Json::Value("OK");
            obj[key] =  Json::Value(value);
            return Json::writeString(builder, obj);
        case ResultType::ERROR:
            obj["result"] = Json::Value("Error");
            obj[key] =  Json::Value(value);
            return Json::writeString(builder, obj);
        default:
            return "";
    }
}

std::string JsonUtility::CMDToJsonString(std::string const& key, std::string const& value) {
    Json::Value obj;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    obj[key] =  Json::Value(value);
    return Json::writeString(builder, obj);
}

ResultType JsonUtility::JsonStringToResult(std::string const& str) {
    Json::CharReaderBuilder jsonBuilder;
    Json::CharReader* JsonReader(jsonBuilder.newCharReader());
    Json::Value obj;
    
    JsonReader->parse(str.c_str(), str.c_str() + str.size(), &obj, nullptr);
    std::string result = obj["result"].asString();
    if (result == "OK") {
        return ResultType::OK;
    } else if (result == "Error") {
        return ResultType::ERROR;
    }
    return ResultType::UKnown;
}

ResultType JsonUtility::JsonStringToResult(std::string const& str, std::string const& key, std::string& value) {
    Json::CharReaderBuilder jsonBuilder;
    Json::CharReader* JsonReader(jsonBuilder.newCharReader());
    Json::Value obj;
    
    JsonReader->parse(str.c_str(), str.c_str() + str.size(), &obj, nullptr);
    std::string result = obj["result"].asString();
    if (result == "OK") {
        value = obj[key].asString();
        return ResultType::OK;
    } else if (result == "Error") {
        value = obj[key].asString();
        return ResultType::ERROR;
    }
    return ResultType::UKnown;
}

std::string JsonUtility::ParseJsonFormatToCString(std::string const& str, std::string const& key)
{
    Json::CharReaderBuilder jsonBuilder;
    Json::CharReader* JsonReader(jsonBuilder.newCharReader());
    Json::Value obj;
    JsonReader->parse(str.c_str(), str.c_str() + str.size(), &obj, nullptr);

    return obj[key].asString();
}

uint32_t JsonUtility::ParseJsonFormatToUInt(std::string str, std::string const& key)
{
    Json::CharReaderBuilder jsonBuilder;
    Json::CharReader* JsonReader(jsonBuilder.newCharReader());
    Json::Value obj;
    JsonReader->parse(str.c_str(), str.c_str() + str.size(), &obj, nullptr);

    return obj[key].asUInt();
}

std::vector<uint32_t> JsonUtility::ParseJsonFormatToUIntArray(std::string str, std::string const& key)
{
    Json::CharReaderBuilder jsonBuilder;
    Json::CharReader* JsonReader(jsonBuilder.newCharReader());
    Json::Value obj;
    JsonReader->parse(str.c_str(), str.c_str() + str.size(), &obj, nullptr);
    Json::Value json_array = obj[key];

    static std::vector<uint32_t> key_vector;
    key_vector.clear();
    if (json_array.isArray()) {
        const uint32_t array_size = json_array.size();
        for (uint32_t i=0; i<array_size; i++)
            key_vector.push_back(json_array[i].asUInt());
    }
    return key_vector;
}
