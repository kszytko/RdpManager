#ifndef FILEJSONLOADER_H
#define FILEJSONLOADER_H

#include <QFile>
#include "jsonloader.h"

class FileJsonLoader : public JsonLoader
{
public:
    FileJsonLoader(QString _filename) : filename(_filename){
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        jsonDoc = QJsonDocument::fromJson(file.readAll());
        file.close();
    }

    // RestApi interface
public:
    bool GetRequest() override;
    QJsonDocument GetParsedResponse() const override;


private:
    QJsonDocument jsonDoc;
    QString filename;
};

#endif // FILEJSONLOADER_H
