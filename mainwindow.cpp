#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include "dataloader.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    DataLoader dataLoader(":/request.json");

    TreeModel *model = new TreeModel(dataLoader, this);


    ui->mainTreeView->setModel(model);
    ui->mainTreeView->expandAll();


}

MainWindow::~MainWindow()
{
    delete ui;
}

