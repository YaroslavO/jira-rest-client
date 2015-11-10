#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NetworkService.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NetworkService *networkService = new NetworkService();
    connect(networkService, SIGNAL(loadProjectFinished(QList<QString>)), this, SLOT(onLoadProjectFinished(QList<QString>)));
    networkService->login("jaroslavo", "secret");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoadProjectFinished(QList<QString> projects) {
    ui->projectsList->addItems(projects);
}

