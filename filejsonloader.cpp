#include "filejsonloader.h"



bool FileJsonLoader::GetRequest(){
    return true;
};

QJsonDocument FileJsonLoader::GetParsedResponse() const {
    return jsonDoc;
};
