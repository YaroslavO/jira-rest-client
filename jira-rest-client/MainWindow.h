#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkAccessManager_;

private slots:
    void onNetworkAccessManagerFinished(QNetworkReply*);
    void onNetworkAccessManagerFinished2(QNetworkReply*);

};

#endif // MAINWINDOW_H
