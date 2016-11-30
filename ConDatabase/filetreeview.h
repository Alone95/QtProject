/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H
#include<QTreeView>
#include<QFileSystemModel>
#include<QDebug>
#include<QStringList>
class FileTreeview : public QTreeView
{
    Q_OBJECT
public:
   explicit FileTreeview(QTreeView *parent=0);


signals:
   void getText(const QString&string);


private slots:
   void test(const QModelIndex&);

private:
    bool FindFile(const QString &path);

private:
    QFileSystemModel *model;

};

#endif // FILETREEVIEW_H
