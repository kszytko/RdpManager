#include <QJsonDocument>
#include <QJsonArray>
#include "dataloader.h"

void DataLoader::downloadWorkPackages() {
    if (jsonLoader->GetRequest())
    {
        QJsonDocument json = jsonLoader->GetParsedResponse();


        QJsonArray wpArray = json["_embedded"]["results"]["_embedded"]["elements"].toArray();
        for (const auto& el : wpArray)
        {
            workPackages.push_back(new WorkPackage(el.toObject()));
        }
    }
}
