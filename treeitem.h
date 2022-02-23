#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>

class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    int childCount() const;
    QList<TreeItem *> children();
    TreeItem *parent();
    bool append(TreeItem* item);
    QVariant data(int column) const;

private:
    QList<TreeItem *> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;

};

#endif // TREEITEM_H
