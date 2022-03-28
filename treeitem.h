#pragma once
#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include "workpackage.h"
#include <memory>

class TreeItem
{
public:
    TreeItem(WorkPackage* _workPackage, TreeItem *parent = nullptr);
    TreeItem(){}
    ~TreeItem();

    int childCount() const;
    QList<TreeItem *> children();
    TreeItem *parent();
    bool append(TreeItem* item);
    void clear();

    QVariant getData(int column) const;

    bool isParentID(const int id) const;

    WorkPackage* getWorkPackage() const;
    bool isMachine();

private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;

    WorkPackage* workPackage;

};

#endif // TREEITEM_H
