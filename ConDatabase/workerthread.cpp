#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent)
    :QThread(parent)
{

}

void WorkerThread::run()
{
    QFileInfoList f1;
    f1=getFileList("G:/");

    qDebug()<<"search is over"<<f1.size();
    emit sendStringlist(stringlist);//像completelineedit发送信号
}


QFileInfoList WorkerThread::getFileList(const QString&path)
{
    QDir dir(path);
    QString filter;
    QFileInfoList file_list =dir.entryInfoList(QDir::Files|QDir::NoSymLinks);
    QFileInfoList folder_list =dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for(int i=0;i!=folder_list.size();i++)
    {
        QString name =folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list =getFileList(name);
        file_list.append(child_file_list);

    }
     foreach(QFileInfo fileinfo,file_list)
     {
        filter= fileinfo.suffix();
        if((filter!="xls")&&(filter!="txt")&&(filter!="jpg")&&(filter!="png"))
        {
            continue;
        }
        stringlist.append(fileinfo.filePath());
     }

     return file_list;
}
