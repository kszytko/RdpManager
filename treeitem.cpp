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

bool TreeItem::append(TreeItem* item)
{
    childItems.push_back(item);
    return true;
}

void TreeItem::clear()
{
    childItems.clear();
}



QVariant TreeItem::getData(int column) const{
    if(workPackage->type == "Machine"){
        switch (column)
        {
        case 0:
           return QVariant(QString::number(workPackage->machineNumber) + " " +  workPackage->subject);
        case 1:
           return QVariant("-------");
        default:
           return QVariant();
        }
    }
    else
    {
        switch (column)
        {
        case 0:
           return QVariant(workPackage->subject);
        case 1:
           return QVariant(workPackage->project);
        default:
            return QVariant();
        }
    }
}

bool TreeItem::isParentID(const int id) const
{
    return workPackage->id == id;
}

WorkPackage* TreeItem::getWorkPackage() const
{
    return workPackage;
}

bool TreeItem::isMachine()
{
    return workPackage->type == "Machine";
}
