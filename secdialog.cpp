#include "secdialog.h"
#include "ui_addTask.h"

secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
}
