#include "ProjectButton.h"


ProjectButton::ProjectButton(const QString name, QString key, QWidget *parent):
    QPushButton(name, parent),
    key_(key)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));
}

void ProjectButton::onButtonClicked() {
    emit clickedWithKey(key_);
}
