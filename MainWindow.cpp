#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NetworkService.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NetworkService *networkService = new NetworkService();
    connect(networkService, SIGNAL(loadProjectFinished(QList<Project*>)), this, SLOT(onLoadProjectFinished(QList<Project*>)));
    networkService->login("jaroslavo", "secret");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoadProjectFinished(QList<Project*> projects) {
    foreach (Project *project, projects) {
        ui->projectsList->addItem(project->name());
    }
}

