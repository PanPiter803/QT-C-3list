#include "createtask.h"
#include "ui_createtask.h"
#include "managementlist.h"
#include "ui_managementlist.h"
#include <QDebug>
#include <QMessageBox>

CreateTask::CreateTask(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::CreateTask)
{
    ui->setupUi(this);
    ui->tasklinkvalue->setEnabled(false);
    iClickedOK = false;
}

CreateTask::~CreateTask()
{
    delete ui;
}

void CreateTask::on_cancel_clicked()
{
    emit cancelcomm("Anulowano");
    iClickedOK = true;
    this->close();
}

void CreateTask::on_createtask_clicked()
{
    if(!ui->tasklinkcheck->isChecked()) ui->taskdescriptionvalue->setText("");
    if(title().isEmpty()) QMessageBox::warning(this, "Błąd", "Pole tytułowe nie może być puste.");
    else
    {
        emit set_values_for_task(important(), title(), description(), link());
        iClickedOK = true;
        this->close();
    }
}

void CreateTask::on_tasklinkcheck_clicked()
{
    if(ui->tasklinkcheck->isChecked()) ui->tasklinkvalue->setEnabled(true);
    else {
        ui->tasklinkvalue->setEnabled(false);
        ui->tasklinkvalue->setText("");
    }
}

void CreateTask::closeEvent(QCloseEvent * event)
{
    if(!iClickedOK)event->ignore();
}

QString CreateTask::title()
{
    return ui->tasktitlevalue->toPlainText();
}

QString CreateTask::description()
{
    return ui->taskdescriptionvalue->toPlainText();
}

QString CreateTask::link()
{
    return ui->tasklinkvalue->toPlainText();
}

QString CreateTask::important()
{
    if(ui->taskimportantcheck->isChecked()) return "ImportantList";
    else return "CurrentList";
}
