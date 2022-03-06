#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include "dataloader.h"
#include "treeitem.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    DataLoader dataLoader(":/request.json");

    TreeModel *model = new TreeModel(dataLoader, this);


    ui->mainTreeView->setModel(model);
    ui->mainTreeView->expandAll();
    ui->mainTreeView->setRootIsDecorated(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonRdpWan_clicked()
{
    QModelIndexList list = ui->mainTreeView->selectionModel()->selectedIndexes();
    QList<QProcess*> processes;

    for(auto & index : list){
        if(index.column() == 0){
            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

            if(item && !item->isMachine())
                item = item->parent();

            if(item && item->isMachine())
            {
                auto wp = item->getWorkPackage();

                QProcess *myProcess = new QProcess(this);
                processes.append(myProcess);


                myProcess->start("mstsc", {"/v:" + wp->wanIP});
            }
        }
    }
}

