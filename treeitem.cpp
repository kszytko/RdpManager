#include "treeitem.h"

TreeItem::TreeItem(WorkPackage* _workPackage, TreeItem *parent) :
    workPackage(_workPackage), parentItem(parent)
{}

int TreeItem::childCount() const{
    return childItems.count();
}

QList<TreeItem *> TreeItem::children(){
    return childItems;
}

TreeItem* TreeItem::parent(){
    return parentItem;
}

bool TreeItem::append(TreeItem *item)
{
    childItems.append(item);
}


QVariant TreeItem::getData(int column) const{
    if(workPackage->type == "Machine"){
        switch (column)
        {
        case 0:
           return QVariant(workPackage->machineNumber);
        case 1:
           return QVariant(workPackage->subject);
        case 2:
           return QVariant(workPackage->project);
        }
    }
    else
    {
        switch (column)
        {
        case 0:
           return QVariant(QString());
        case 1:
           return QVariant(workPackage->subject);
        case 2:
           return QVariant(workPackage->project);
        }
    }
}
