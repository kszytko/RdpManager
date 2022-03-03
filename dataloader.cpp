#include <QJsonDocument>
#include <QJsonArray>
#include "dataloader.h"

void DataLoader::downloadWorkPackages() {
    QJsonDocument json;

    if (jsonLoader->GetRequest())
    {
        json = jsonLoader->GetParsedResponse();


        QJsonArray wpArray = json["_embedded"]["results"]["_embedded"]["elements"].toArray();
        for (const auto& el : wpArray)
        {
            workPackages.push_back(std::make_shared<WorkPackage>(el));
        }
    }
}
