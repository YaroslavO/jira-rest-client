#ifndef PROJECTBUTTON_H
#define PROJECTBUTTON_H

#include <QPushButton>


class ProjectButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ProjectButton(const QString name, QString key, QWidget *parent = 0);

signals:
    void clickedWithKey(QString key);

private:
    QString key_;

private slots:
    void onButtonClicked();
};

#endif // PROJECTBUTTON_H
