#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QStringList headers({tr("Title"), tr("Description")});

    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll(), this);
    file.close();

    ui->mainTreeView->setModel(model);



}

MainWindow::~MainWindow()
{
    delete ui;
}

