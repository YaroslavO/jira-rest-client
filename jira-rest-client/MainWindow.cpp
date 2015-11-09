#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QJsonObject requestData;
    requestData["username"] = "jaroslavo";
    requestData["password"] = "secret";

    QJsonDocument requestDocument;
    requestDocument.setObject(requestData);

    QUrl url("http://taho2.interlink-ua.com:8080/rest/auth/1/session");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_ = new QNetworkAccessManager();
    networkAccessManager_->post(request, requestDocument.toJson());
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessManagerFinished(QNetworkReply*)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onNetworkAccessManagerFinished(QNetworkReply *reply) {
    disconnect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessManagerFinished(QNetworkReply*)));
    connect(networkAccessManager_, SIGNAL(finished(QNetworkReply*)), this, SLOT(onNetworkAccessManagerFinished2(QNetworkReply*)));

    QUrl url("http://taho2.interlink-ua.com:8080/rest/api/2/project");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    networkAccessManager_->get(request);
}

void MainWindow::onNetworkAccessManagerFinished2(QNetworkReply *reply) {
    QByteArray data(reply->readAll());
    QJsonDocument json = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = json.array();

    foreach (const QJsonValue &value, jsonArray) {
        QJsonObject obj = value.toObject();
        qDebug() << obj["name"].toString();
    }
}
