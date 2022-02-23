#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) :
    itemData(data), parentItem(parent)
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
    return itemData.at(column);
}
