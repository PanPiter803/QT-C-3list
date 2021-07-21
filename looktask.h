#ifndef LOOKTASK_H
#define LOOKTASK_H

#include "managementlist.h"
#include <QDialog>

namespace Ui {
class looktask;
}

class looktask : public QDialog
{
    Q_OBJECT

public:
    explicit looktask(QWidget *parent = nullptr);
    ~looktask();
    void takevalues(QString,QString,QString);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;

private slots:
    void on_link_clicked();
    void on_back_clicked();

private:
    Ui::looktask *ui;
};

#endif // LOOKTASK_H
