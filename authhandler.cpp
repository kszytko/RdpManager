#include "authhandler.h"
#include <QDebug>

AuthHandler::AuthHandler(QObject *parent)
    : QObject{parent}, m_apiKey(QString())
{
    m_networkAccessManager = new QNetworkAccessManager( this );
    connect(m_networkAccessManager, &QNetworkAccessManager::authenticationRequired,
            this, &AuthHandler::authenticate);

}

AuthHandler::~AuthHandler()
{
    m_networkAccessManager->deleteLater();
}

void AuthHandler::setApiKey(const QString &apiKey)
{
    m_apiKey = apiKey;
}

void AuthHandler::downloadData()
{
    QString dataEndpoint = "http://10.137.24.110/api/v3/queries/284";
    performGET(dataEndpoint);
}

QJsonDocument AuthHandler::getParsedJson()
{
    return m_parsedReply;
}



void AuthHandler::authenticate(QNetworkReply *reply, QAuthenticator *auth)
{
    Q_UNUSED(reply);

    if(!auth){
        auth = new QAuthenticator();
    }

    auth->setUser("apikey");
    auth->setPassword(m_apiKey);

    qDebug() << "Authenticate";
}

void AuthHandler::performGET(const QString &url)
{
    QNetworkRequest request((QUrl(url)));
    request.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
    m_networkReply = m_networkAccessManager->get(request);
    connect(m_networkReply, &QNetworkReply::finished, this, &AuthHandler::networkReplyReadyRead);
    //connect(m_networkReply, QNetworkReply::NetworkError, this, SLOT(slotErrorWorkoutList(QNetworkReply::NetworkError)));
}


void AuthHandler::networkReplyReadyRead()
{
    if(m_networkReply->error() != QNetworkReply::NoError){
        return;
    }

    auto statusCode = m_networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << QVariant(statusCode).toString();


    QByteArray response = m_networkReply->readAll();
    m_networkReply->deleteLater();

    parseResponse(response);

}
void AuthHandler::parseResponse(const QByteArray &response)
{
    m_parsedReply = QJsonDocument::fromJson(response);

    emit dataParsed();
}

