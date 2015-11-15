#include "Project.h"


Project::Project(QString name, QString key) {
    name_ = name;
    key_ = key;
}

QString Project::name() const {
    return name_;
}

QString Project::key() const {
    return key_;
}
