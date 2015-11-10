#include "NetworkService.h"

const QString AUTHORIZATION_URL = "http://taho2.interlink-ua.com:8080/rest/auth/1/session";

NetworkService::NetworkService(QObject *parent) : QObject(parent) {
    networkAccessManager_ = new QNetworkAccessManager();
}

void NetworkService::login(QString username, QString password) {
    QJsonObject requestData;
    requestData["username"] = username;
    requestData["password"] = password;

    QJsonDocument requestDocument;
    requestDocument.setObject(requestData);

    QUrl url(AUTHORIZATION_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_->post(request, requestDocument.toJson());
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthorizationFinished(QNetworkReply*)));
}

void NetworkService::onAuthorizationFinished(QNetworkReply *) {
    disconnect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthorizationFinished(QNetworkReply*)));
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onLoadProjectsFinished(QNetworkReply*)));

    QUrl url("http://taho2.interlink-ua.com:8080/rest/api/2/project");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_->get(request);
}

void NetworkService::onLoadProjectsFinished(QNetworkReply *reply) {
    QByteArray data(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = json.array();

    QList<QString> projects;
    foreach (const QJsonValue &value, jsonArray) {
        QJsonObject obj = value.toObject();
        projects.append(obj["name"].toString());
    }

    emit loadProjectFinished(projects);
}

