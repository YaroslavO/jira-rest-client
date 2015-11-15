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
    networkService_ = new NetworkService();
    connect(networkService_, SIGNAL(loadProjectFinished(QList<Project*>)), this, SLOT(onLoadProjectFinished(QList<Project*>)));
    connect(networkService_, SIGNAL(issueLoaded(QList<QString>)), this, SLOT(onLoadIssue(QList<QString>)));
    networkService_->login("jaroslavo", "secret");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoadProjectFinished(QList<Project*> projects) {
    ui->projectsList->clear();

    foreach (Project *project, projects) {
        std::auto_ptr_ref<QListWidgetItem> item(new QListWidgetItem(ui->projectsList));
        ProjectButton *projectButton = new ProjectButton(project->name(), project->key(), this);

        connect(projectButton, SIGNAL(clickedWithKey(QString)), networkService_, SLOT(onProjectButtonClicked(QString)));

        ui->projectsList->setItemWidget(item._M_ptr, (QWidget*) projectButton);
    }
}

void MainWindow::onLoadIssue(QList<QString> issues) {

}

