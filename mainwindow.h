#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include "workpackage.h"
#include "treemodel.h"
#include "dataloader.h"
#include "treeitem.h"
typedef QList<std::shared_ptr<WorkPackage>> QWorkPackageList;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonRdpWan_clicked();
    void on_buttonRdpLan_clicked();
    void on_buttonTeamViewer_clicked();
    void on_buttonRefresh_clicked();

private:
    QWorkPackageList GetSelectedWorkPackages(QModelIndexList list);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
