#pragma once
#include <QString>
#include <QJsonObject>
#include <iostream>

class WorkPackage {
public:
    WorkPackage(const QJsonObject&);
    WorkPackage(QString _type, int _id, int _machineNumber, QString _subject)
        :type(_type), id(_id), subject(_subject), machineNumber(_machineNumber)
    {}
    WorkPackage( QString _type,  int _parentID,QString _subject)
        : type(_type), parentID(_parentID), subject(_subject)
    {}

private:
    int getHrefID(const QJsonValue&) const;
    QString getString(const QJsonValue&) const;
    int getInt(const QJsonValue&) const;

public:
    bool isType(const QJsonObject& json, const QString& type) const;
	virtual void print() const;

    friend std::ostream& operator<<(std::ostream& out, const QString &str){
        return out << str.toLatin1().constData();
    }

public:
    int	id = 0;
    QString type;
    QString subject;
    QString description;
    QString startDate;
    QString dueDate;
    QString estimatedTime;
    QString createdAt;
    QString updatedAt;

    QString priority;
    QString project;
    QString status;
    QString parentName;
    int parentID;

    QString loginName = "";
    QString lanIP = "";
    QString wanIP = "";
    int teamViewerID = 0;
    int machineNumber = 0;
};

