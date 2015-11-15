#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NetworkService.h"
#include <memory>
#include "ProjectButton.h"

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
    ui->projectsList->clear();

    foreach (Project *project, projects) {
        std::auto_ptr_ref<QListWidgetItem> item(new QListWidgetItem(ui->projectsList));
        ProjectButton *projectButton = new ProjectButton(project->name(), project->key(), this);

        ui->projectsList->setItemWidget(item._M_ptr, (QWidget*) projectButton);
    }
}

