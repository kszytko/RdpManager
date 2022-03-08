#include "restapijsonloader.h"
#include <QNetworkAccessManager>

RestApiJsonLoader::RestApiJsonLoader(const QString& serverAdress,const QString& apikey, const int querryID)
{

}

bool RestApiJsonLoader::GetRequest()
{
    QNetworkRequest request(QUrl("http://hapi.fhir.org/baseDstu3/Patient/4705560"));
        request.setRawHeader("Content-Type", "application/fhir+json");

            manager.put(request, doc.toJson());
        }
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
