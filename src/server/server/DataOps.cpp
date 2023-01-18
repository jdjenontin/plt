#include "DataOps.h"

namespace server {
    /**
     * @brief Convert Json::Value object to string object
    */
    std::string DataOps::jsonToString(Json::Value jsonData)
    {
        Json::StyledWriter writer;
        std::string stringData = writer.write(jsonData);

        return stringData;
    }

    /**
     * @brief Convert string object to Json::Value object
    */
    Json::Value DataOps::stringToJson(std::string stringData)
    {
        Json::Value jsonValue;
        Json::Reader reader;
        reader.parse(stringData, jsonValue);
        
        return jsonValue;
    }
}