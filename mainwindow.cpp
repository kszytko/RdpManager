#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QProcess>


#include "authdata.h"

#include "workpackage.h"
#include "restapijsonloader.h"
#include "filejsonloader.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    handler = new AuthHandler();
    handler->setApiKey(AUTH::APIKEY);
    handler->downloadData();

    connect(handler, &AuthHandler::dataParsed, this, &MainWindow::downloadJson);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonRdpWan_clicked()
{
    QList<WorkPackage*> workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
    QString program = "mstsc";

    for(const auto & wp : workPackages){
        QStringList arguments;
        arguments << "/v:" <<  wp->wanIP;

        QProcess::startDetached(program, arguments);
    }
}



void MainWindow::on_buttonRdpLan_clicked()
{
    QList<WorkPackage*> workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
    QString program = "mstsc";

    for(const auto & wp : workPackages){
        QStringList arguments;
        arguments << "/v:" <<  wp->lanIP;

        QProcess::startDetached(program, arguments);
    }
}


void MainWindow::on_buttonTeamViewer_clicked()
{
    QList<WorkPackage*> workPackages = GetSelectedWorkPackages(ui->mainTreeView->selectionModel()->selectedIndexes());
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



}

void MainWindow::downloadJson()
{
    m_json = handler->getParsedJson();

    setNewModel();
}

void MainWindow::setNewModel()
{
    QList<WorkPackage*> workPackages;
    //QJsonDocument json = apiLoader.GetParsedResponse();
    QJsonArray jsonWorkPackages = m_json["_embedded"]["results"]["_embedded"]["elements"].toArray();

    for (const auto& el : jsonWorkPackages)
    {
        workPackages.push_back(new WorkPackage(el.toObject()));
    }

    model = new TreeModel(workPackages, this);

    ui->mainTreeView->setModel(model);
    ui->mainTreeView->expandAll();
    ui->mainTreeView->setRootIsDecorated(false);
}



QList<WorkPackage*> MainWindow::GetSelectedWorkPackages(QModelIndexList list){
   QList<WorkPackage*> workPackages;

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
