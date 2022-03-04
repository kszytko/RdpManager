#pragma once
#ifndef RESTAPIJSONLOADER_H
#define RESTAPIJSONLOADER_H

#include "jsonloader.h"

class RestApiJsonLoader : public JsonLoader
{
public:
    RestApiJsonLoader(const QString& serverAdress,const QString& apikey, const int querryID);

    // JsonLoader interface
public:
    bool GetRequest() override;
    QJsonDocument GetParsedResponse() const override;
};

#endif // RESTAPIJSONLOADER_H
