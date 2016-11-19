/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef COMPLETELINEEDIT_H
#define COMPLETELINEEDIT_H

#include <QtGui>
#include<QLineEdit>
#include <QStringList>
#include<workerthread.h>

class QListView;
class QStringListModel;
class QModelIndex;

class CompleteLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    //CompleteLineEdit(QStringList words, QWidget *parent = 0);
    CompleteLineEdit(QWidget *parent=0);

public slots:
    void setCompleter(const QString &text); // 动态的显示完成列表
    void completeText(const QModelIndex &index); // 点击完成列表中的项，使用此项自动完成输入的单词
    void getStringList(const QStringList&stringlist);//从子线程中获取列表

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

private:
    QStringList words; // 整个完成列表的单词
    QListView *listView; // 完成列表
    QStringListModel *model; // 完成列表的model
    WorkerThread *workerthread;

};

#endif // COMPLETELINEEDIT_H
