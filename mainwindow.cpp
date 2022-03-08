#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <QProcess>

#include "authdata.h"



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
    QWorkPackageList workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
    QString program = "mstsc";

    for(const auto & wp : workPackages){
        QStringList arguments;
        arguments << "/v:" <<  wp->wanIP;

        QProcess::startDetached(program, arguments);
    }
}



void MainWindow::on_buttonRdpLan_clicked()
{
    QWorkPackageList workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
    QString program = "mstsc";

    for(const auto & wp : workPackages){
        QStringList arguments;
        arguments << "/v:" <<  wp->lanIP;

        QProcess::startDetached(program, arguments);
    }
}


void MainWindow::on_buttonTeamViewer_clicked()
{
    QWorkPackageList workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
    QString program = "C:\\Program Files (x86)\\TeamViewer\\TeamViewer.exe";

    for(const auto & wp : workPackages){
        QStringList arguments;
        arguments << "-i" << QString::number(wp->teamViewerID);
        arguments << "--Password" << AUTH::TV::PASSWORD;
        arguments << "-Minimize";

        QProcess::startDetached(program, arguments);
    }

}


void MainWindow::on_buttonRefresh_clicked()
{
    DataLoader* dataLoader = new DataLoader(AUTH::SERVER_ADRESS, AUTH::APIKEY, AUTH::QUERRY_ID);
    TreeModel *model = new TreeModel(*dataLoader, this);


    ui->mainTreeView->setModel(model);
    //ui->mainTreeView-
}

QWorkPackageList MainWindow::GetSelectedWorkPackages(QModelIndexList list){
   QWorkPackageList workPackages;

    for(const auto & index : list){
        if(index.column() == 0){
            TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

            if(item && !item->isMachine()){
                item = item->parent();
            }

            if(item && item->isMachine()){
                workPackages.append(item->getWorkPackage());
            }
        }
    }
}

