#include "filetreeview.h"
#include<QDirModel>
FileTreeview::FileTreeview(QTreeView *parent)
    :QTreeView(parent)
{
    model =new QFileSystemModel();
    model->setRootPath("");
    this->setModel(model);
    this->setRootIndex(model->index(""));
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(test(QModelIndex)));
}



void FileTreeview::test(const QModelIndex &index)
{

    qDebug()<<model->filePath(index);
    QString filePath=(model->filePath(index));

    emit getText(filePath);

}


//bool FileTreeview::FindFile(const QString & path)
//{
//    QDir dir(path);
//    if (!dir.exists())
//        return false;
//    dir.setFilter(QDir::Dirs|QDir::Files);
//    dir.setSorting(QDir::DirsFirst);
//    QFileInfoList list = dir.entryInfoList();
//    int i=0;
//    do{

//        QFileInfo fileInfo = list.at(i);
//        if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")
//        {
//            i++;
//            continue;
//        }
//        bool bisDir=fileInfo.isDir();
//        if(bisDir)
//        {
//           // nFiles++;
//            qDebug() << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
//                                    .arg(fileInfo.fileName(),10).arg(fileInfo.path()))<<endl;

//            FindFile(fileInfo.filePath());
//        }
//        else{
//            //nFiles++;
//            qDebug() << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
//                                    .arg(fileInfo.fileName(),10).arg(fileInfo.path()))<<endl;
//        }
//        i++;
//    }while(i<list.size());
//    return true;
//}
