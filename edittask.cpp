#include "edittask.h"
#include "ui_edittask.h"
#include "managementlist.h"
#include "ui_managementlist.h"
#include <QDebug>
#include <QMessageBox>

EditTask::EditTask(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::EditTask)
{
    ui->setupUi(this);
    ui->tasklinkvalue->setEnabled(false);
    ui->taskimportantcheck->setEnabled(false);
    iClickedOK = false;
}

EditTask::~EditTask()
{
    delete ui;
}

void EditTask::on_cancel_clicked()
{
    emit cancelcomm("Anulowano");
    iClickedOK = true;
    this->close();
}

void EditTask::takevalues(QString slistname, QString stitle, QString sdescription, QString slink, QModelIndex Index)
{
    ui->tasktitlevalue->setText(stitle);
    ui->taskdescriptionvalue->setText(sdescription);
    if(slistname == "ImportantList") ui->taskimportantcheck->setChecked(true);
    if(!slink.isEmpty())
    {
        ui->tasklinkcheck->setChecked(true);
        ui->tasklinkvalue->setEnabled(true);
        ui->tasklinkvalue->setText(slink);
    }
    oIndex = Index;
}

void EditTask::on_createtask_clicked()
{
    if(title().isEmpty()) QMessageBox::warning(this, "Błąd", "Pole tytułowe nie może być puste.");
    else
    {
        emit set_values_for_task(important(), title(), description(), link(), oIndex);
        qDebug() << title();
        iClickedOK = true;
        this->close();
    }
}

void EditTask::on_tasklinkcheck_clicked()
{
    if(ui->tasklinkcheck->isChecked()) ui->tasklinkvalue->setEnabled(true);
    else {
        ui->tasklinkvalue->setEnabled(false);
        ui->tasklinkvalue->setText("");
    }
}

void EditTask::closeEvent(QCloseEvent * event)
{
    if(!iClickedOK)event->ignore();
}

QString EditTask::title()
{
    return ui->tasktitlevalue->toPlainText();
}

QString EditTask::description()
{
    return ui->taskdescriptionvalue->toPlainText();
}

QString EditTask::link()
{
    return ui->tasklinkvalue->toPlainText();
}

QString EditTask::important()
{
    if(ui->taskimportantcheck->isChecked()) return "ImportantList";
    else return "CurrentList";
}
