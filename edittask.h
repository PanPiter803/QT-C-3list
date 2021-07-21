#ifndef EDITTASK_H
#define EDITTASK_H

#include "managementlist.h"
#include <QDialog>

namespace Ui {
class EditTask;
}

class EditTask : public QDialog
{
    Q_OBJECT

public:
    explicit EditTask(QWidget *parent = nullptr);
    ~EditTask();
    void takevalues(QString,QString,QString,QString,QModelIndex);
    QString title();
    QString description();
    QString link();
    QString important();

signals:
    void set_values_for_task(QString,QString,QString,QString,QModelIndex);
    void cancelcomm(QString);

private slots:
    void closeEvent(QCloseEvent *event);
    void on_cancel_clicked();
    void on_createtask_clicked();
    void on_tasklinkcheck_clicked();

private:
    Ui::EditTask *ui;
    QModelIndex oIndex;
    bool iClickedOK;
};

#endif // EDITTASK_H
