#ifndef PROJECT_H
#define PROJECT_H

#include <QString>


class Project {
public:
    Project(QString name, QString key);

    QString name() const;

    QString key() const;

private:
    QString name_;
    QString key_;

};

#endif // PROJECT_H
