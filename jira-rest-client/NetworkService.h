#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QtNetwork>


class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = 0);

    void login(QString username, QString password);

signals:
    void loadProjectFinished(QList<QString>);

private:
    QNetworkAccessManager *networkAccessManager_;

private slots:
    void onAuthorizationFinished(QNetworkReply*);
    void onLoadProjectsFinished(QNetworkReply*);
};

#endif // NETWORKSERVICE_H
