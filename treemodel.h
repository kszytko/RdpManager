#pragma once
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QList>

#include "treeitem.h"
#include "dataloader.h"
#include "workpackage.h"

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(QList<WorkPackage*> workPackages, QObject *parent = nullptr);
    ~TreeModel() = default;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void updateModelData(QList<WorkPackage*> workPackages);
private:  
    void setupModelData(QList<WorkPackage*> workPackages, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;

private:
    TreeItem * rootItem;
    QList<QVariant> headers;

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // TREEMODEL_H
