#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QJsonDocument>

class AuthHandler : public QObject
{
    Q_OBJECT
public:
    explicit AuthHandler(QObject *parent = nullptr);
    ~AuthHandler();
    void setApiKey(const QString & apiKey);
    void downloadData();
    QJsonDocument getParsedJson();

public slots:
    void networkReplyReadyRead();
    void authenticate(QNetworkReply * reply, QAuthenticator * auth);

signals:
    void dataParsed();

private:
    void performGET(const QString & url);
    void parseResponse(const QByteArray & response);

    QString m_apiKey;
    QJsonDocument m_parsedReply;

    QNetworkAccessManager * m_networkAccessManager;
    QNetworkReply * m_networkReply;

};

#endif // AUTHHANDLER_H
