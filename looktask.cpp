#include "looktask.h"
#include "ui_looktask.h"
#include "QDesktopServices"
#include "QUrl"
#include "QDebug"

looktask::looktask(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::looktask)
{
    ui->setupUi(this);
}

looktask::~looktask()
{
    delete ui;
}

void looktask::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void looktask::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void looktask::on_link_clicked()
{
    QString link = ui->link->text();
    QDesktopServices::openUrl(QUrl(link));
}

void looktask::takevalues(QString stitle, QString sdescription, QString slink)
{
    ui->title->setText(stitle);
    ui->description->setText(sdescription);
    if(!slink.isEmpty() || slink != "" || QUrl(slink).isValid()) ui->link->setText(slink);
    else
    {
        ui->link->hide();
        ui->description->setGeometry(10, 50, 501, 307);
    }
}


void looktask::on_back_clicked()
{
    this->close();
}

