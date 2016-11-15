#include "treeview.h"
#include <QTextCodec>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
TreeView::TreeView() :
    QTreeView()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    model = new QStandardItemModel(4,2);
    model->setHeaderData(0,Qt::Horizontal,tr("service"));
    model->setHeaderData(1,Qt::Horizontal,tr("Details"));
    QStandardItem *item1 = new QStandardItem("avahi-daemon");
    item1->setIcon(QIcon("F:/czcl/czcl/DockWidget/logo.png"));
    QStandardItem *item2 = new QStandardItem("bluetooth");
    item2->setIcon(QIcon("F:/czcl/czcl/DockWidget/logo.png"));
    QStandardItem *item3 = new QStandardItem("crond");
    item3->setIcon(QIcon("F:/czcl/czcl/DockWidget/logo.png"));
    QStandardItem *item4 = new QStandardItem("cups");
    item4->setIcon(QIcon("F:/czcl/czcl/DockWidget/logo.png"));
    model->setItem(0,0,item1);
    model->setItem(1,0,item2);
    model->setItem(2,0,item3);
    model->setItem(3,0,item4);
    QModelIndex parent;
    for(int i=0;i<4;i++)
    {
        parent=model->index(0,0,parent);
        model->insertRows(0,1,parent);
        model->insertColumns(0,1,parent);
        QModelIndex index=model->index(0,0,parent);
        model->setData(index,"dslpjfkjgop");
    }
    this->setModel(model);
}

void TreeView::iterateOverItems()
{
   QList<QStandardItem *>list = returnTheItems();
   foreach (QStandardItem* item, list) {
       qDebug()<<item->text();

   }
}

QList<QStandardItem *> TreeView::returnTheItems()
{
    return model->findItems("*",Qt::MatchWildcard|Qt::MatchRecursive);
}

void TreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QModelIndex indexo=currentIndex();
        QFileInfo minfo(indexo.data().toString());
        if(!minfo.exists())
        {
            QMessageBox::warning(0,"error",minfo.absoluteFilePath()+"is no fill");
        }
        QMessageBox::about(0,"info",minfo.absoluteFilePath());

        qDebug()<<indexo.data().toString();
    }
}
