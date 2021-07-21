#ifndef MANAGEMENTLIST_H
#define MANAGEMENTLIST_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QListView>
#include <QStringListModel>
#include "ui_managementlist.h"
#include "createtask.h"
#include "edittask.h"
#include "looktask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ManagementList; }
QT_END_NAMESPACE

class ManagementList : public QMainWindow
{
    Q_OBJECT

public:
    ManagementList(QWidget *parent = nullptr);
    ~ManagementList();
    QModelIndex cIndex, iIndex, fIndex;


protected:
    bool eventFilter(QObject *watched = nullptr, QEvent *event = nullptr);
    QPoint mousePoint;
    QPoint dragPosition;

private:
    Ui::ManagementList *ui;
    void setLists();
    void loadTasks();
    void whichList(QString, QString, QString, QString);
    void whichList(QString, QString, QString, QString, int);
    QString isImportant(bool);
    bool validItem(QModelIndex);
    void onRemove(QString, QModelIndex);
    void replaceItemsUP(QString, int);
    void replaceItemsDOWN(QString, int);

    QString currentListName[30] = {};
    QString currentTitle[30] = {};
    QString currentDescription[30] = {};
    QString currentLink[30] = {};

    QString importantListName[30] = {};
    QString importantTitle[30] = {};
    QString importantDescription[30] = {};
    QString importantLink[30] = {};

    QString finishedListName[30] = {};
    QString finishedTitle[30] = {};
    QString finishedDescription[30] = {};
    QString finishedLink[30] = {};

public slots:
    void after_creating(QString, QString, QString, QString);
    void after_editing(QString, QString, QString, QString, QModelIndex);
    void after_cancel();

private slots:
    void closeProgram();
    void minimalizeProgram();
    void maximalizeProgram();
    void onAdd();
    void onEdit();
    void onRemove();
    void on_SaveButton_clicked();
    void on_LoadButton_clicked();
    void on_setImportantAct_clicked();
    void on_setActual_clicked();
    void on_setFinished_clicked();
    void on_setImportantFin_clicked();
    void on_OpenButton_clicked();
    void on_cTOP_clicked();
    void on_cUP_clicked();
    void on_cLOW_clicked();
    void on_cBOTTOM_clicked();
    void on_iTOP_clicked();
    void on_iUP_clicked();
    void on_iLOW_clicked();
    void on_iBOTTOM_clicked();
    void on_CurrentTasksList_doubleClicked(const QModelIndex &index);
    void on_ImportantTasksList_doubleClicked(const QModelIndex &index);
    void on_FinishedTasksList_doubleClicked(const QModelIndex &index);
    void on_CurrentTasksList_clicked(const QModelIndex &index);
    void on_ImportantTasksList_clicked(const QModelIndex &index);
    void on_FinishedTasksList_clicked(const QModelIndex &index);
};



#endif // MANAGEMENTLIST_H
