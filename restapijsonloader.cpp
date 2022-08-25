#include "restapijsonloader.h"
#include <QNetworkAccessManager>

RestApiJsonLoader::RestApiJsonLoader(const QString& serverAdress,const QString& apikey, const int querryID)
{

}

bool RestApiJsonLoader::GetRequest()
{

}

QJsonDocument RestApiJsonLoader::GetParsedResponse() const
{
    return QJsonDocument();
}

/*
        QFile file("/path/of/themostsimplepatientJSON.json");
        if(file.open(QIODevice::ReadOnly)){
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonObject obj = doc.object();
            obj["id"] = "4705560"; // add ID
            doc.setObject(obj);
*/
