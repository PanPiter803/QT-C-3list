#include "managementlist.h"
#include "ui_managementlist.h"
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QList>

ManagementList::ManagementList(QWidget *parent)
    : QMainWindow(parent,Qt::FramelessWindowHint),
      ui(new Ui::ManagementList)
{
    ui->setupUi(this);
    ui->UpperBar->installEventFilter(this);
    ui->AddTask->setIcon(QIcon(":Assets/addicon.png"));
    ui->EditTask->setIcon(QIcon(":Assets/editicon.png"));
    ui->RemoveTask->setIcon(QIcon(":Assets/deleteicon.png"));
    ui->SaveButton->setIcon(QIcon(":Assets/saveicon.png"));
    ui->LoadButton->setIcon(QIcon(":Assets/saveicon.png"));
    connect(ui->CloseButton, SIGNAL(released()), this, SLOT(closeProgram()));
    connect(ui->MaximalizeButton, SIGNAL(released()), this, SLOT(maximalizeProgram()));
    connect(ui->MinimalizeButton, SIGNAL(released()), this, SLOT(minimalizeProgram()));
    connect(ui->AddTask, SIGNAL(released()), this, SLOT(onAdd()));
    connect(ui->EditTask, SIGNAL(released()), this, SLOT(onEdit()));
    connect(ui->RemoveTask, SIGNAL(released()), this, SLOT(onRemove()));
    setLists();

    cIndex = ui->CurrentTasksList->model()->index(0,0);
    iIndex = ui->ImportantTasksList->model()->index(0,0);
    fIndex = ui->FinishedTasksList->model()->index(0,0);
}

ManagementList::~ManagementList()
{
    delete ui;
}

void ManagementList::on_OpenButton_clicked()
{
    qDebug() << cIndex << iIndex << fIndex;
    if(!validItem(cIndex) && !validItem(iIndex) && !validItem(fIndex)) QMessageBox::warning(this, "Błąd", "Nie zaznaczono aktywnego zadania.");
    else
    {
        looktask* looktask = new class looktask(this);
        if(validItem(cIndex) && !validItem(iIndex) && !validItem(fIndex))
        {
            qDebug() << currentTitle[cIndex.row()] << currentDescription[cIndex.row()] << currentLink[cIndex.row()];
            looktask->takevalues(currentTitle[cIndex.row()], currentDescription[cIndex.row()], currentLink[cIndex.row()]);
        }
        else if(!validItem(cIndex) && validItem(iIndex) && !validItem(fIndex))
        {
            qDebug() << importantTitle[cIndex.row()] << importantDescription[cIndex.row()] << importantLink[cIndex.row()];
            looktask->takevalues(importantTitle[iIndex.row()], importantDescription[iIndex.row()], importantLink[iIndex.row()]);

        }
        else if(!validItem(cIndex) && !validItem(iIndex) && validItem(fIndex))
        {
            looktask->takevalues(finishedTitle[fIndex.row()], finishedDescription[fIndex.row()], finishedLink[fIndex.row()]);
        }
        looktask->exec();
    }
}

//Minimize, maximize and close program buttons
void ManagementList::closeProgram()
{
    QCoreApplication::quit();
}

void ManagementList::maximalizeProgram()
{
    if(!isMaximized())
    {
        showMaximized();
    }
    else
    {
        showNormal();
    }
}

void ManagementList::minimalizeProgram()
{
    showMinimized();
}

//Moving frameless window with mouse
bool ManagementList::eventFilter(QObject *hover, QEvent *event)
{
    if (hover == ui->UpperBar)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
            if (mouse_event->button() == Qt::LeftButton)
            {
                dragPosition = mouse_event->globalPos() - frameGeometry().topLeft();
                return false;
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
            if (mouse_event->buttons() & Qt::LeftButton)
            {
                move(mouse_event->globalPos() - dragPosition);
                return false;
            }
        }
    }
    return false;
}

//Lists settings
void ManagementList::setLists()
{
    ui->CurrentTasksList->setDragEnabled(false);
    ui->CurrentTasksList->setAcceptDrops(false);
    ui->CurrentTasksList->setDropIndicatorShown(false);
    ui->CurrentTasksList->setDragDropOverwriteMode(false);
    ui->CurrentTasksList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CurrentTasksList->setModel(new QStringListModel());
    ui->CurrentTasksList->setStyleSheet
    ("QListView {font-size: 10pt; font-weight: bold; color: white; border: 3px solid rgba(0,0,0,1); border-top-right-radius: 15px; border-top-left-radius: 15px; border-bottom-right-radius: 15px; border-bottom-left-radius: 15px; background-color: rgba(0,0,0,1);}"
    "QListView::item {background-color: rgba(220, 0, 0, 1); padding: 5%; border: 1px solid black; border-top-right-radius: 10px; border-top-left-radius: 10px; border-bottom-right-radius: 10px; border-bottom-left-radius: 10px;}"
    "QListView::item::hover {background-color: rgba(200, 20, 0, 1); color: white;}"
    "QListView::item::selected {background-color: rgba(255, 255, 255, 1); border: none; color: black;}");

    ui->ImportantTasksList->setDragEnabled(false);
    ui->ImportantTasksList->setAcceptDrops(false);
    ui->ImportantTasksList->setDropIndicatorShown(false);
    ui->ImportantTasksList->setDragDropOverwriteMode(false);
    ui->ImportantTasksList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ImportantTasksList->setModel(new QStringListModel());
    ui->ImportantTasksList->setStyleSheet
    ("QListView {font-size: 10pt; font-weight: bold; color: white; border: 3px solid rgba(255,0,0,1); border-top-right-radius: 15px; border-top-left-radius: 15px; border-bottom-right-radius: 15px; border-bottom-left-radius: 15px; background-color: rgba(255,0,0,1);}"
    "QListView::item {background-color: rgba(0, 0, 0, 1); padding: 5%; border: 1px solid black; border-top-right-radius: 10px; border-top-left-radius: 10px; border-bottom-right-radius: 10px; border-bottom-left-radius: 10px;}"
    "QListView::item::hover {background-color: rgba(50, 50, 50, 1); color: white;}"
    "QListView::item::selected {background-color: rgba(255, 255, 255, 1); border: none; color: black;}");

    ui->FinishedTasksList->setDragEnabled(true);
    ui->FinishedTasksList->setAcceptDrops(true);
    ui->FinishedTasksList->setDropIndicatorShown(true);
    ui->FinishedTasksList->setDragDropOverwriteMode(false);
    ui->FinishedTasksList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->FinishedTasksList->setModel(new QStringListModel());
    ui->FinishedTasksList->setStyleSheet
    ("QListView {font-size: 10pt; font-weight: bold; color: white; border: 3px solid rgba(0,0,0,1); border-top-right-radius: 15px; border-top-left-radius: 15px; border-bottom-right-radius: 15px; border-bottom-left-radius: 15px; background-color: rgba(0,0,0,1);}"
    "QListView::item {background-color: rgba(220, 0, 0, 1); padding: 5%; border: 1px solid black; border-top-right-radius: 10px; border-top-left-radius: 10px; border-bottom-right-radius: 10px; border-bottom-left-radius: 10px;}"
    "QListView::item::hover {background-color: rgba(200, 20, 0, 1); color: white;}"
    "QListView::item::selected {background-color: rgba(255, 255, 255, 1); border: none; color: black;}");
}

//Creating a new window for new task
void ManagementList::onAdd()
{
    ManagementList::setEnabled(false);
    CreateTask* createtask = new CreateTask(this);
    connect(createtask, SIGNAL(set_values_for_task(QString,QString,QString,QString)), this, SLOT(after_creating(QString,QString,QString,QString)));
    connect(createtask, SIGNAL(cancelcomm(QString)), this, SLOT(after_cancel()));
    createtask->exec();
}
//Creating a new window for editing current task
void ManagementList::onEdit()
{
    cIndex = ui->CurrentTasksList->currentIndex();
    iIndex = ui->ImportantTasksList->currentIndex();
    if(!validItem(cIndex) && !validItem(iIndex)) QMessageBox::warning(this, "Błąd", "Nie zaznaczono aktywnego zadania.");
    else
    {
        ManagementList::setEnabled(false);
        EditTask* edittask = new EditTask(this);
        if(validItem(cIndex) && !validItem(iIndex))
        {
            edittask->takevalues(currentListName[cIndex.row()], currentTitle[cIndex.row()], currentDescription[cIndex.row()], currentLink[cIndex.row()], cIndex);
        }
        else if(!validItem(cIndex) && validItem(iIndex))
        {
            edittask->takevalues(importantListName[iIndex.row()], importantTitle[iIndex.row()], importantDescription[iIndex.row()], importantLink[iIndex.row()], iIndex);
        }
        connect(edittask, SIGNAL(set_values_for_task(QString,QString,QString,QString,QModelIndex)), this, SLOT(after_editing(QString,QString,QString,QString,QModelIndex)));
        connect(edittask, SIGNAL(cancelcomm(QString)), this, SLOT(after_cancel()));
        edittask->exec();
    }
}

//Inserting values to lists
void ManagementList::after_creating(QString listname, QString title, QString description, QString link)
{
    ManagementList::setEnabled(true);
    whichList(listname, title, description, link);
}
//Editing values
void ManagementList::after_editing(QString listname, QString title, QString description, QString link, QModelIndex Index)
{
    ManagementList::setEnabled(true);
    whichList(listname, title, description, link, Index.row());
}

//After clicking cancel in new window
void ManagementList::after_cancel()
{
    ManagementList::setEnabled(true);
}

//Removing values from list
void ManagementList::onRemove()
{
    if(validItem(ui->CurrentTasksList->currentIndex())) ui->CurrentTasksList->model()->removeRow(ui->CurrentTasksList->currentIndex().row());
    else if(validItem(ui->ImportantTasksList->currentIndex())) ui->ImportantTasksList->model()->removeRow(ui->ImportantTasksList->currentIndex().row());
    else if(validItem(ui->FinishedTasksList->currentIndex())) ui->FinishedTasksList->model()->removeRow(ui->FinishedTasksList->currentIndex().row());
    else QMessageBox::warning(this, "Błąd", "Nie zaznaczono żadnego zadania.");
}
//Removing values from list
void ManagementList::onRemove(QString listtitle, QModelIndex Index)
{
    if(listtitle == "CurrentList") ui->CurrentTasksList->model()->removeRow(Index.row());
    else if(listtitle == "ImportantList") ui->ImportantTasksList->model()->removeRow(Index.row());
    else if(listtitle == "FinishedList") ui->FinishedTasksList->model()->removeRow(Index.row());
    else QMessageBox::warning(this, "Błąd", "Nie zaznaczono żadnego zadania.");
}
//Inserting values to list
void ManagementList::whichList(QString listtitle, QString title, QString description, QString link)
{
    QModelIndex oIndex;
    if(listtitle == "CurrentList")
    {
        ui->CurrentTasksList->model()->insertRow(ui->CurrentTasksList->model()->rowCount());
        oIndex = ui->CurrentTasksList->model()->index(ui->CurrentTasksList->model()->rowCount() - 1, 0);
        ui->CurrentTasksList->model()->setData(oIndex, title);
        currentListName[oIndex.row()] = listtitle;
        currentTitle[oIndex.row()] = title;
        currentDescription[oIndex.row()] = description;
        currentLink[oIndex.row()] = link;
        qDebug() << oIndex.row() << currentListName[oIndex.row()] << currentTitle[oIndex.row()] << currentDescription[oIndex.row()] << currentLink[oIndex.row()];
    }
    else if(listtitle == "ImportantList")
    {
        ui->ImportantTasksList->model()->insertRow(ui->ImportantTasksList->model()->rowCount());
        oIndex = ui->ImportantTasksList->model()->index(ui->ImportantTasksList->model()->rowCount() - 1, 0);
        ui->ImportantTasksList->model()->setData(oIndex, title);
        importantListName[oIndex.row()] = listtitle;
        importantTitle[oIndex.row()] = title;
        importantDescription[oIndex.row()] = description;
        importantLink[oIndex.row()] = link;
        qDebug() << oIndex.row() << importantListName[oIndex.row()] << importantTitle[oIndex.row()] << importantDescription[oIndex.row()] << importantLink[oIndex.row()];
    }
    else if(listtitle == "FinishedList")
    {
        ui->FinishedTasksList->model()->insertRow(ui->FinishedTasksList->model()->rowCount());
        oIndex = ui->FinishedTasksList->model()->index(ui->FinishedTasksList->model()->rowCount() - 1, 0);
        ui->FinishedTasksList->model()->setData(oIndex, title);
        finishedListName[oIndex.row()] = listtitle;
        finishedTitle[oIndex.row()] = title;
        finishedDescription[oIndex.row()] = description;
        finishedLink[oIndex.row()] = link;
        qDebug() << oIndex.row() << finishedListName[oIndex.row()] << finishedTitle[oIndex.row()] << finishedDescription[oIndex.row()] << finishedLink[oIndex.row()];
    }
}
//Inserting edited values to list
void ManagementList::whichList(QString listtitle, QString title, QString description, QString link, int row)
{
    QModelIndex oIndex;
    if(listtitle == "CurrentList")
    {
        oIndex = ui->CurrentTasksList->model()->index(row, 0);
        ui->CurrentTasksList->model()->setData(oIndex, title);
        currentListName[oIndex.row()] = listtitle;
        currentTitle[oIndex.row()] = title;
        currentDescription[oIndex.row()] = description;
        currentLink[oIndex.row()] = link;
    }
    else if(listtitle == "ImportantList")
    {
        oIndex = ui->ImportantTasksList->model()->index(row, 0);
        ui->ImportantTasksList->model()->setData(oIndex, title);
        importantListName[oIndex.row()] = listtitle;
        importantTitle[oIndex.row()] = title;
        importantDescription[oIndex.row()] = description;
        importantLink[oIndex.row()] = link;
    }
    else if(listtitle == "FinishedList")
    {
        oIndex = ui->FinishedTasksList->model()->index(row, 0);
        ui->FinishedTasksList->model()->setData(oIndex, title);
        finishedListName[oIndex.row()] = listtitle;
        finishedTitle[oIndex.row()] = title;
        finishedDescription[oIndex.row()] = description;
        finishedLink[oIndex.row()] = link;
    }
}

//Checking if item is valid
bool ManagementList::validItem(QModelIndex index)
{
    if(index.isValid()) return true;
    else return false;
}
//Current to Important
void ManagementList::on_setImportantAct_clicked()
{
    if(validItem(cIndex))
    {
        whichList("ImportantList", currentTitle[cIndex.row()], currentDescription[cIndex.row()], currentLink[cIndex.row()]);
        currentListName[cIndex.row()].clear();
        currentTitle[cIndex.row()].clear();
        currentDescription[cIndex.row()].clear();
        currentLink[cIndex.row()].clear();

        int i = cIndex.row();
        if(i != ui->CurrentTasksList->model()->rowCount()-1)
        {
            do
            {
                replaceItemsDOWN("CurrentList", i);
                i++;
            }while(i < ui->CurrentTasksList->model()->rowCount()-1);
        }

        onRemove("CurrentList", ui->CurrentTasksList->model()->index(i, 0));
    }
}
//Important to Current
void ManagementList::on_setActual_clicked()
{
    if(validItem(iIndex))
    {
        whichList("CurrentList", importantTitle[iIndex.row()], importantDescription[iIndex.row()], importantLink[iIndex.row()]);
        importantListName[iIndex.row()].clear();
        importantTitle[iIndex.row()].clear();
        importantDescription[iIndex.row()].clear();
        importantLink[iIndex.row()].clear();

        int i = iIndex.row();
        if(i != ui->ImportantTasksList->model()->rowCount()-1)
        {
            do
            {
                replaceItemsDOWN("FinishedList", i);
                i++;
            }while(i < ui->ImportantTasksList->model()->rowCount()-1);
        }

        onRemove("ImportantList", ui->ImportantTasksList->model()->index(i, 0));
    }
}
//Important to Finished
void ManagementList::on_setFinished_clicked()
{
    if(validItem(iIndex))
    {
        whichList("FinishedList", importantTitle[iIndex.row()], importantDescription[iIndex.row()], importantLink[iIndex.row()]);
        importantListName[iIndex.row()].clear();
        importantTitle[iIndex.row()].clear();
        importantDescription[iIndex.row()].clear();
        importantLink[iIndex.row()].clear();

        int i = iIndex.row();
        if(i != ui->ImportantTasksList->model()->rowCount()-1)
        {
            do
            {
                replaceItemsDOWN("FinishedList", i);
                i++;
            }while(i < ui->ImportantTasksList->model()->rowCount()-1);
        }

        onRemove("ImportantList", ui->ImportantTasksList->model()->index(i, 0));
    }
}
//Finished to Important
void ManagementList::on_setImportantFin_clicked()
{
    if(validItem(fIndex))
    {
        whichList("ImportantList", finishedTitle[fIndex.row()], finishedDescription[fIndex.row()], finishedLink[fIndex.row()]);
        finishedListName[fIndex.row()].clear();
        finishedTitle[fIndex.row()].clear();
        finishedDescription[fIndex.row()].clear();
        finishedLink[fIndex.row()].clear();

        int i = fIndex.row();
        if(i != ui->FinishedTasksList->model()->rowCount()-1)
        {
            do
            {
                replaceItemsDOWN("FinishedList", i);
                i++;
            }while(i < ui->FinishedTasksList->model()->rowCount()-1);
        }

        onRemove("FinishedList", ui->FinishedTasksList->model()->index(i, 0));
    }
}
//Save
void ManagementList::on_SaveButton_clicked()
{
    QFile file("C://Users/"+qgetenv("USERNAME")+"/Documents/Tasks.txt");

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Błąd", "Wystąpił problem z zapisem danych.");
    }
    QTextStream out(&file);

    for(int i=0; i<30; i++)
    {
        if(!currentListName[i].isEmpty())
        {
            out << currentListName[i] + "," + currentTitle[i] +","+ currentDescription[i] + "," + currentLink[i] << endl;
        }
        else i++;
    }

    for(int i=0; i<30; i++)
    {
        if(!importantListName[i].isEmpty())
        {
            out << importantListName[i] + "," + importantTitle[i] + "," + importantDescription[i] + "," + importantLink[i] << endl;
        }
        else i++;
    }

    for(int i=0; i<30; i++)
    {
        if(!finishedListName[i].isEmpty())
        {
            out << finishedListName[i] + "," + finishedTitle[i] + "," + finishedDescription[i] + "," + finishedLink[i] << endl;
        }
        else i++;
    }
    file.flush();
    file.close();
    QMessageBox::information(this, "Zapisano", "Zapisano.");
}
//Load
void ManagementList::on_LoadButton_clicked()
{
    QFile file("C://Users/"+qgetenv("USERNAME")+"/Documents/Tasks.txt");
    cIndex = ui->CurrentTasksList->model()->index(0, 0);
    iIndex = ui->ImportantTasksList->model()->index(0, 0);
    fIndex = ui->FinishedTasksList->model()->index(0, 0);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Błąd", "Wystąpił błąd z wczytaniem danych. Nie znaleziono pliku.");
    }

    QTextStream in(&file);
    QString line;
    QStringList list;

    for(int i = 0; i < 30; i++)
    {
        onRemove("CurrentList", cIndex);
        cIndex = ui->CurrentTasksList->model()->index(cIndex.row()+1, 0);
    }

    for(int i = 0; i < 30; i++)
    {
        onRemove("ImportantList", iIndex);
        iIndex = ui->ImportantTasksList->model()->index(iIndex.row()+1, 0);
    }

    for(int i = 0; i < 30; i++)
    {
        onRemove("FinishedList", fIndex);
        fIndex = ui->FinishedTasksList->model()->index(fIndex.row()+1, 0);
    }

    do
    {
        line = in.readLine();
        if(!line.isEmpty())
        {
            list = line.split(",");
            whichList(list[0], list[1], list[2], list[3]);
        }
    }while(!line.isNull());

    file.flush();
    file.close();
}

//Placing value on top of the list
void ManagementList::on_cTOP_clicked()
{
    int i = ui->CurrentTasksList->currentIndex().row();
    do
    {
        replaceItemsUP("CurrentList", i);
        i--;
    }
    while(i > 0);
    ui->FinishedTasksList->clearSelection();
}

//Placing value higher
void ManagementList::on_cUP_clicked()
{
    replaceItemsUP("CurrentList", ui->CurrentTasksList->currentIndex().row());
    ui->FinishedTasksList->clearSelection();
}

//Placing value lower
void ManagementList::on_cLOW_clicked()
{
    replaceItemsDOWN("CurrentList", ui->CurrentTasksList->currentIndex().row());
    ui->FinishedTasksList->clearSelection();
}

//Placing value on bottom of the list
void ManagementList::on_cBOTTOM_clicked()
{
    int i = ui->CurrentTasksList->currentIndex().row();;
    do
    {
        replaceItemsDOWN("CurrentList", i);
        i++;
    }
    while(i < ui->CurrentTasksList->model()->rowCount()-1);
    ui->FinishedTasksList->clearSelection();
}


void ManagementList::on_iTOP_clicked()
{
    qDebug() <<"click";
    int i = ui->ImportantTasksList->currentIndex().row();
    do
    {
        replaceItemsUP("ImportantList", i);
        i--;
    }
    while(i > 0);
    ui->FinishedTasksList->clearSelection();
}


void ManagementList::on_iUP_clicked()
{
    replaceItemsUP("ImportantList", ui->ImportantTasksList->currentIndex().row());
    ui->FinishedTasksList->clearSelection();
    qDebug() <<"click";
}


void ManagementList::on_iLOW_clicked()
{
    qDebug() <<"click";
    replaceItemsDOWN("ImportantList", ui->ImportantTasksList->currentIndex().row());
    ui->FinishedTasksList->clearSelection();
}


void ManagementList::on_iBOTTOM_clicked()
{
    qDebug() <<"click";
    int i = ui->ImportantTasksList->currentIndex().row();;
    do
    {
        replaceItemsDOWN("ImportantList", i);
        i++;
    }
    while(i < ui->ImportantTasksList->model()->rowCount()-1);
    ui->FinishedTasksList->clearSelection();
}
//Replacing to top
void ManagementList::replaceItemsUP(QString listname, int row)
{
    if(listname == "CurrentList")
    {
        QModelIndex Index = ui->CurrentTasksList->model()->index(row, 0);
        if(Index.row() > 0)
        {
            QString tempListName, tempTitle, tempDescription, tempLink;

            tempListName = currentListName[Index.row()];
            tempTitle = currentTitle[Index.row()];
            tempDescription = currentDescription[Index.row()];
            tempLink = currentLink[Index.row()];

            currentListName[Index.row()] = currentListName[Index.row()-1];
            currentTitle[Index.row()] = currentTitle[Index.row()-1];
            currentDescription[Index.row()] = currentDescription[Index.row()-1];
            currentLink[Index.row()] = currentLink[Index.row()-1];

            currentListName[Index.row()-1] = tempListName;
            currentTitle[Index.row()-1] = tempTitle;
            currentDescription[Index.row()-1] = tempDescription;
            currentLink[Index.row()-1] = tempLink;

            ui->CurrentTasksList->model()->setData(Index, currentTitle[Index.row()]);
            Index = ui->CurrentTasksList->model()->index(Index.row()-1, 0);
            ui->CurrentTasksList->model()->setData(Index, currentTitle[Index.row()]);
        }
    }
    else if(listname == "ImportantList")
    {
        QModelIndex Index = ui->ImportantTasksList->model()->index(row, 0);
        if(Index.row() > 0)
        {
            QString tempListName, tempTitle, tempDescription, tempLink;

            tempListName = importantListName[Index.row()];
            tempTitle = importantTitle[Index.row()];
            tempDescription = importantDescription[Index.row()];
            tempLink = importantLink[Index.row()];

            importantListName[Index.row()] = importantListName[Index.row()-1];
            importantTitle[Index.row()] = importantTitle[Index.row()-1];
            importantDescription[Index.row()] = importantDescription[Index.row()-1];
            importantLink[Index.row()] = importantLink[Index.row()-1];

            importantListName[Index.row()-1] = tempListName;
            importantTitle[Index.row()-1] = tempTitle;
            importantDescription[Index.row()-1] = tempDescription;
            importantLink[Index.row()-1] = tempLink;

            ui->ImportantTasksList->model()->setData(Index, importantTitle[Index.row()]);
            Index = ui->ImportantTasksList->model()->index(Index.row()-1, 0);
            ui->ImportantTasksList->model()->setData(Index, importantTitle[Index.row()]);
        }
    }
}
//Replacing to bottom
void ManagementList::replaceItemsDOWN(QString listname, int row)
{
    if(listname == "CurrentList")
    {
        QModelIndex Index = ui->CurrentTasksList->model()->index(row, 0);
        if(Index.row() != ui->CurrentTasksList->model()->rowCount()-1)
        {
            QString tempListName, tempTitle, tempDescription, tempLink;

            tempListName = currentListName[Index.row()];
            tempTitle = currentTitle[Index.row()];
            tempDescription = currentDescription[Index.row()];
            tempLink = currentLink[Index.row()];

            currentListName[Index.row()] = currentListName[Index.row()+1];
            currentTitle[Index.row()] = currentTitle[Index.row()+1];
            currentDescription[Index.row()] = currentDescription[Index.row()+1];
            currentLink[Index.row()] = currentLink[Index.row()+1];

            currentListName[Index.row()+1] = tempListName;
            currentTitle[Index.row()+1] = tempTitle;
            currentDescription[Index.row()+1] = tempDescription;
            currentLink[Index.row()+1] = tempLink;

            ui->CurrentTasksList->model()->setData(Index, currentTitle[Index.row()]);
            Index = ui->CurrentTasksList->model()->index(Index.row()+1, 0);
            ui->CurrentTasksList->model()->setData(Index, currentTitle[Index.row()]);
        }
    }
    else if(listname == "ImportantList")
    {
        QModelIndex Index = ui->ImportantTasksList->model()->index(row, 0);
        if(Index.row() != ui->ImportantTasksList->model()->rowCount()-1)
        {
            QString tempListName, tempTitle, tempDescription, tempLink;

            tempListName = importantListName[Index.row()];
            tempTitle = importantTitle[Index.row()];
            tempDescription = importantDescription[Index.row()];
            tempLink = importantLink[Index.row()];

            importantListName[Index.row()] = importantListName[Index.row()+1];
            importantTitle[Index.row()] = importantTitle[Index.row()+1];
            importantDescription[Index.row()] = importantDescription[Index.row()+1];
            importantLink[Index.row()] = importantLink[Index.row()+1];

            importantListName[Index.row()+1] = tempListName;
            importantTitle[Index.row()+1] = tempTitle;
            importantDescription[Index.row()+1] = tempDescription;
            importantLink[Index.row()+1] = tempLink;

            ui->ImportantTasksList->model()->setData(Index, importantTitle[Index.row()]);
            Index = ui->ImportantTasksList->model()->index(Index.row()+1, 0);
            ui->ImportantTasksList->model()->setData(Index, importantTitle[Index.row()]);
        }
    }
    else if(listname == "FinishedList")
    {
        QModelIndex Index = ui->FinishedTasksList->model()->index(row, 0);
        if(Index.row() > 0)
        {
            QString tempListName, tempTitle, tempDescription, tempLink;

            tempListName = finishedListName[Index.row()];
            tempTitle = finishedTitle[Index.row()];
            tempDescription = finishedDescription[Index.row()];
            tempLink = finishedLink[Index.row()];

            finishedListName[Index.row()] = finishedListName[Index.row()-1];
            finishedTitle[Index.row()] = finishedTitle[Index.row()-1];
            finishedDescription[Index.row()] = finishedDescription[Index.row()-1];
            finishedLink[Index.row()] = finishedLink[Index.row()-1];

            finishedListName[Index.row()-1] = tempListName;
            finishedTitle[Index.row()-1] = tempTitle;
            finishedDescription[Index.row()-1] = tempDescription;
            finishedLink[Index.row()-1] = tempLink;

            ui->FinishedTasksList->model()->setData(Index, importantTitle[Index.row()]);
            Index = ui->FinishedTasksList->model()->index(Index.row()-1, 0);
            ui->FinishedTasksList->model()->setData(Index, importantTitle[Index.row()]);
        }
    }
}


void ManagementList::on_CurrentTasksList_doubleClicked(const QModelIndex &index)
{
    cIndex = index;
    iIndex = ui->ImportantTasksList->model()->index(-1,-1);
    fIndex = ui->FinishedTasksList->model()->index(-1,-1);
    on_OpenButton_clicked();
}


void ManagementList::on_ImportantTasksList_doubleClicked(const QModelIndex &index)
{
    cIndex = ui->ImportantTasksList->model()->index(-1,-1);
    iIndex = index;
    fIndex = ui->FinishedTasksList->model()->index(-1,-1);
    on_OpenButton_clicked();
}

void ManagementList::on_FinishedTasksList_doubleClicked(const QModelIndex &index)
{
    cIndex = ui->FinishedTasksList->model()->index(-1,-1);
    iIndex = ui->ImportantTasksList->model()->index(-1,-1);
    fIndex = index;
    on_OpenButton_clicked();
}


void ManagementList::on_CurrentTasksList_clicked(const QModelIndex &index)
{
    ui->ImportantTasksList->clearSelection();
    ui->FinishedTasksList->clearSelection();
    cIndex = index;
    iIndex = ui->ImportantTasksList->model()->index(-1,-1);
    fIndex = ui->FinishedTasksList->model()->index(-1,-1);
}


void ManagementList::on_ImportantTasksList_clicked(const QModelIndex &index)
{
    ui->CurrentTasksList->clearSelection();
    ui->FinishedTasksList->clearSelection();
    cIndex = ui->ImportantTasksList->model()->index(-1,-1);
    iIndex = index;
    fIndex = ui->FinishedTasksList->model()->index(-1,-1);
}


void ManagementList::on_FinishedTasksList_clicked(const QModelIndex &index)
{
    ui->CurrentTasksList->clearSelection();
    ui->ImportantTasksList->clearSelection();
    iIndex = ui->ImportantTasksList->model()->index(-1,-1);
    cIndex = ui->FinishedTasksList->model()->index(-1,-1);
    fIndex = index;
}

