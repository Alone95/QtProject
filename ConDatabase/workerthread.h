/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include<QThread>
#include<QDebug>
#include<QFileInfoList>
#include<QStringList>
#include<QDir>
#include<QFileInfo>
class WorkerThread : public QThread
{
    Q_OBJECT
public:
   explicit WorkerThread(QObject *parent = 0);
protected:
    void run();
private slots:

private:
    QFileInfoList getFileList(const QString&path);
private:
    QStringList stringlist;

signals:

    void sendStringlist(const QStringList&stringlist);

};

#endif // WORKERTHREAD_H
