#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel(const QStringList& headers, const QString &data,
            QObject *parent = nullptr);
    ~TreeModel();

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);

private:
    TreeItem * rootItem;
};

#endif // TREEMODEL_H
