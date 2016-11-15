#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QStandardItem>
#include <QList>
#include <QMouseEvent>
#include <QHeaderView>
#include <QDebug>
class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView();
    void iterateOverItems();
    QList<QStandardItem *> returnTheItems();
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    QStandardItemModel *model;
signals:
    
public slots:
    
};

#endif // TREEVIEW_H
