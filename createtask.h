#ifndef CREATETASK_H
#define CREATETASK_H

#include "managementlist.h"
#include <QDialog>

namespace Ui {
class CreateTask;
}

class CreateTask : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTask(QWidget *parent = nullptr);
    ~CreateTask();
    QString title();
    QString description();
    QString link();
    QString important();

signals:
    void set_values_for_task(QString, QString, QString, QString);
    void cancelcomm(QString);

private slots:
    void closeEvent(QCloseEvent *event);
    void on_cancel_clicked();
    void on_createtask_clicked();
    void on_tasklinkcheck_clicked();

private:
    Ui::CreateTask *ui;
    bool iClickedOK;
};

#endif // CREATETASK_H
