#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QJsonDocument>

class JsonLoader
{

public:
    virtual bool GetRequest() = 0;
    virtual QJsonDocument GetParsedResponse() const = 0;
};



#endif // JSONLOADER_H
