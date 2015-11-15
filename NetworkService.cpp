#include "NetworkService.h"


const QString AUTHORIZATION_URL = "http://taho2.interlink-ua.com:8080/rest/auth/1/session";
const QString PROJECT_URL = "http://taho2.interlink-ua.com:8080/rest/api/2/project";
const QString SEARCH_URL = "http://taho2.interlink-ua.com:8080/rest/api/2/search";

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

void NetworkService::onProjectButtonClicked(QString key) {
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onLoadIssues(QNetworkReply*)));

    QUrl url(SEARCH_URL + "?jql=project=\""+ key +"\"");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_->get(request);
}

void NetworkService::onAuthorizationFinished(QNetworkReply *) {
    disconnect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthorizationFinished(QNetworkReply*)));
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onLoadProjectsFinished(QNetworkReply*)));

    QUrl url(PROJECT_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_->get(request);
}

void NetworkService::onLoadProjectsFinished(QNetworkReply *reply) {
    QByteArray data(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = json.array();

    QList<Project*> projects;
    foreach (const QJsonValue &value, jsonArray) {
        QJsonObject obj = value.toObject();
        projects.append(new Project(obj["name"].toString(), obj["key"].toString()));
    }

    emit loadProjectFinished(projects);
    disconnect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onLoadProjectsFinished(QNetworkReply*)));
}

void NetworkService::onLoadIssues(QNetworkReply *reply) {
    QByteArray data(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = json.object();
    QJsonArray issues = jsonObject["issues"].toArray();

    qDebug() << issues;
}

