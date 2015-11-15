#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Project.h"

class NetworkService;

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
    NetworkService *networkService_;

private slots:
    void onLoadProjectFinished(QList<Project*> projects);
    void onLoadIssue(QList<QString> issues);

};

#endif // MAINWINDOW_H
