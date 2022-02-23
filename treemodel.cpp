#include "treemodel.h"

#include <QtWidgets>

TreeModel::TreeModel(const QStringList& headers, const QString &data, QObject *parent)
    : QAbstractItemModel{parent}
{
    QList<QVariant> rootData;
    for(const auto &header : headers){
        rootData << header;
    }

    rootItem = new TreeItem(rootData);
    setupModelData(data.split('\n'), rootItem);
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {

}

QModelIndex TreeModel::parent(const QModelIndex &child) const{

}

int TreeModel::rowCount(const QModelIndex &parent) const{

}

int TreeModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 2;
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



void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent){
    QList<TreeItem *> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
            QList<QVariant> columnData;
            columnData.reserve(columnStrings.size());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->children().last();
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->append(new TreeItem(columnData, parent));
        }
        ++number;
    }
}
