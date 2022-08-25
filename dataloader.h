#pragma once

#ifndef DATALOADER_H
#define DATALOADER_H


#include <memory>
#include "workpackage.h"
#include "restapijsonloader.h"
#include "filejsonloader.h"


class DataLoader
{
public:
    DataLoader(const QString serverAdress, const QString apikey,const  int querryID){
        jsonLoader = std::make_unique<RestApiJsonLoader>(serverAdress, apikey, querryID);
        downloadWorkPackages();
    }

    DataLoader(const QString filename) {
        jsonLoader = std::make_unique<FileJsonLoader>(filename);
        downloadWorkPackages();
    }

    QList<WorkPackage*> workPackages;

private:
    void downloadWorkPackages();

private:
    std::unique_ptr<JsonLoader> jsonLoader;
};


#endif // DATALOADER_H
