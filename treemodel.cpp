#include "treemodel.h"

#include <QtWidgets>
#include "workpackage.h"


TreeModel::TreeModel(const DataLoader &dataLoader, QObject *parent)
    : QAbstractItemModel{parent}
{
    headers << "Number";
    headers << "Name";
    headers << "Text";


    rootItem = new TreeItem();
    setupModelData(dataLoader, rootItem);
}

void TreeModel::setupModelData(const DataLoader &dataLoader, TreeItem *parent){
    // setup pop music
    for (const auto& el : dataLoader.workPackages) {
        if (el->type == "Machine") {
            parent->append(new TreeItem(el));
        }
    }


    for (const auto& el : dataLoader.workPackages) {
        if (el->type == "MachineTask") {
            const auto& children = parent->children();
            auto found = std::find_if(children.begin(), children.end(), [&](const TreeItem* node) {
                return node->isParentID(el->parentID);
            });
            if (found != children.end()) {
                TreeItem* newItem = new TreeItem(el, *found);
                (*found)->append(newItem);
            }
        }
    }



}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->children().at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const{
    if(!index.isValid()){
        return QModelIndex();
    }
    TreeItem *parentItem = nullptr;
    TreeItem *childItem = getItem(index);

    if(childItem){
        parentItem = childItem->parent();
    }

    if(parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childCount(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid() && parent.column() > 0)
        return 0;

    const TreeItem *parentItem = getItem(parent);

    if(parentItem)
        return parentItem->childCount();
    return 0;
}

int TreeModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return headers.size();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);
    return item->getData(index.column());
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const{
    if(index.isValid()){
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headers[section];
    }

    return QVariant();
}




