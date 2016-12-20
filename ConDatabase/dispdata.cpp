#include "dispdata.h"


Dispdata::Dispdata(QListWidget*parent)
    :QListWidget(parent)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    clickedTimer=new QTimer;
    isDouble=false;
    this->setAutoScroll(true);
    this->setViewMode(QListWidget::ListMode);//设置显示模式
    this->setSortingEnabled(true);//设置自动排序
    this->setStyleSheet("QListWidget::item:selected{background-color:rgb(100,222,232)}");//设置选中项颜色
    this->connsql();//连接数据库
    this->display();//显示数据
    this->setCurrentRow(0);
    this->setMouseTracking(true);//鼠标监测
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(handleTransfer(QListWidgetItem*)));//单双击识别
    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(handleListWidgetDoubleClick()));//双击
    connect(clickedTimer,SIGNAL(timeout()),this,SLOT(handleListWidgetSingleClick()));//单击

}

Dispdata::~Dispdata()
{

}

/*显示数据库中的数据*/
void Dispdata::display()
{
    QSqlQuery *sqlTable =new QSqlQuery();
    QString sqlstr ="select name from blob_example";
    this->setIconSize(QSize(50,30));
    sqlTable->prepare(sqlstr);
    if(sqlTable->exec())
    {
        while(sqlTable->next())
        {

            listWidgetItem =new QListWidgetItem;
            listWidgetItem->setText(QString(sqlTable->value(0).toString()));
            judge_filetype(QString(sqlTable->value(0).toString()));//判断类型
            listWidgetItem->setSizeHint(QSize(30,30));
            listWidgetItem->setForeground(Qt::black);//前景色
            listWidgetItem->setToolTip(QString(sqlTable->value(0).toString()));
            listWidgetItem->setFont(QFont("等线 Light",20));
            this->addItem(listWidgetItem);

        }
    }

    sqlTable->clear();

}

void Dispdata::judge_filetype(const QString&filename)
{

    QString str;
    str=filename.section('.',-1,-1);//分割字符串
    if(str=="txt")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/text.png"));
    else if(str=="mp3")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/mp3.png"));
    else if(str=="zip")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/zip.png"));
    else if(str=="rar")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/rar.png"));
    else if(str=="exe")
        listWidgetItem->setIcon(QIcon(":/myImages/images/exe.ico"));
    else if(str=="doc"||str=="docx")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/docx_win.png"));
    else if(str=="ppt"||str=="pptx"||str=="pps"||str=="ppsx")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/pptx_win.png"));
    else if(str=="xls"||str=="xlsx")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/xlsx_win.png"));
    else if(str=="pdf")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/pdf.png"));
    else if(str=="png")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/png.png"));
    else if(str=="jpg")
        listWidgetItem->setIcon(QIcon(":/myImages/images/icon/jpeg.png"));
    else
        listWidgetItem->setIcon(QIcon(":/myImages/images/yafeilinux.png"));


}

/*连接oracle数据库*/
void Dispdata::connsql()
{

    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("172.22.136.170");
    db.setDatabaseName("orcl");
    db.setUserName("lds");
    db.setPassword("123456");
    db.setPort(1521);

    if (!db.open())
    {
        qDebug()<<QObject::tr(("error\n"));
    }
    else
    {
        qDebug()<<"succeess";
    }

}
/*鼠标右键点击出现菜单*/
void Dispdata::contextMenuEvent(QContextMenuEvent *)
{
    QMenu* popMenu = new QMenu(this);
    QAction *add= new QAction("添加",this);
    QAction *del=new QAction("删除",this);
    QAction *upd= new QAction("重命名",this);
    connect(add,SIGNAL(triggered(bool)),this,SLOT(add_data()));
    connect(del,SIGNAL(triggered(bool)),this,SLOT(del_data()));
    connect(upd,SIGNAL(triggered(bool)),this,SLOT(upd_data()));
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(changed()));
    popMenu->addAction(add);

    if(this->itemAt(mapFromGlobal(QCursor::pos()))!=NULL)//如果有item才能修改
    {
        popMenu->addAction(upd);
        popMenu->addAction(del);
    }

    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置

}




void Dispdata::add_data()
{
    QSqlQuery add;
    QStringList fileName =QFileDialog::getOpenFileNames(this,tr("文件对话框"),"./","ALL FILE(*.*)");
    qDebug()<<fileName.size();
    if(fileName.size()!=0)
    {
        for(int i=0;i<fileName.size();i++)
        {
            QFile file(fileName[i]);
            if(file.open(QIODevice::ReadOnly))
            {
                qWarning("open data");
            }
            QByteArray binarydata;
            binarydata =file.readAll();
            qWarning("Data size: %d",binarydata.size());
            file.close();//关闭QFile
            QVariant var(binarydata);
            if(!add.exec("CREATE TABLE blob_example(name varchar(70), blob_col BLOB)"))
            {
                qWarning("table is exist");
            }
            if (!add.prepare( "INSERT INTO blob_example ( name, blob_col ) VALUES ( ?, ? )" ) ) {
                qWarning( "Unable to prepare query" );

            }
            add.bindValue(0,fileName[i]);
            add.bindValue(1,var);
            if(add.exec()){
                qWarning("Enable to execute prepared query");
                listWidgetItem =new QListWidgetItem;
                listWidgetItem->setText(QString(fileName[i]));
                judge_filetype(QString(fileName[i]));
                listWidgetItem->setSizeHint(QSize(30,30));
                listWidgetItem->setToolTip(QString(fileName[i]));
                listWidgetItem->setForeground(Qt::black);//前景色
                listWidgetItem->setFont(QFont("等线 Light",20));
                this->addItem(listWidgetItem);
            }

        }

        add.clear();
        this->show();
    }



}

void Dispdata::del_data()
{
    QString url =this->currentItem()->text();
    qDebug()<<url<<" "<<this->currentItem()->text();
    QSqlQuery colquery;
    colquery.prepare("delete from blob_example where name =:filename");
    colquery.bindValue(":filename",url);
    if(colquery.exec())
    {
        QTime t;
        t.start();
        while(t.elapsed() < 2000)
        {

        }
        QMessageBox::information(this,tr("提示"),tr("删除成功"));
        QListWidgetItem *listWidgetItem = this->currentItem();
        this->removeItemWidget(listWidgetItem);
        delete listWidgetItem;
//        colquery.finish();
    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("删除失败"));
    }

    this->show();

}


void Dispdata::upd_data()
{
    this->openPersistentEditor(this->currentItem());
    this->editItem(this->currentItem());
    QString old= this->currentItem()->text();
    qDebug()<<old;
}


QString Dispdata::changed()
{
    QString old= this->currentItem()->text();
    this->closePersistentEditor(this->currentItem());
    return old;
}

/*键盘响应事件*/
void Dispdata::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:{

        QString old_name;
        old_name = changed();
        qDebug()<<old_name;
        QString new_name;
        new_name= this->currentItem()->text();
        qDebug()<<new_name;
        if(!(old_name==new_name))//如果名字被修改，则进行操作
        {

            QSqlQuery updata;
            updata.prepare("update blob_example  set name =:newname where name =:oldname");
            updata.bindValue(":newname",new_name);
            updata.bindValue(":oldname",old_name);
            updata.exec();
        }
        else{
            qDebug()<<"未进行更改操作"<<endl;
            down_data();//进行下载操作
        }
        break;
    }
    case Qt::Key_Up:{
        int i=this->currentRow();
        if(i==0)
        {
            setCurrentRow(this->count()-1);
        }
        else
            setCurrentRow(--i);

        break;
    }
    case Qt::Key_Down:{

        int i=this->currentRow();
        if(i==this->count()-1)
        {
            setCurrentRow(0);
        }
        else
            setCurrentRow(++i);
        break;
    }


    default:
        break;
    }




}

void Dispdata::handleListWidgetSingleClick()
{
    if(!isDouble)
    {

    }
}

void Dispdata::handleListWidgetDoubleClick(){

    isDouble=true;
    clickedTimer->stop();
    down_data();
}

void Dispdata::handleTransfer(QListWidgetItem *)
{
    if(isDouble)
    {
        isDouble=true;
    }
    else
    {
        clickedTimer->start(120);
    }
    isDouble =false;
}

/*鼠标左键点击*/
void Dispdata::down_data()
{
    bool isdownload =true;
    QString url =this->currentItem()->text();
    qDebug()<<url;
    QString str;
    str=url.section('\\',-1,-1);//分割字符串
    QString str2;
    str2=url.section('.',-1,-1);
    qDebug()<<"文件的名字为"<<str<<" "<<str2;

    QDir dir(QDir::currentPath()+"/download/");
    qDebug()<<QDir::currentPath()+"/download/";
    if(dir.exists())//如果路径存在，判断文件是否被下载
    {
        dir.setFilter(QDir::Files|QDir::NoSymLinks);
        QFileInfoList list =dir.entryInfoList();
        for(int i=0;i<list.count();i++)
        {
            QFileInfo fileinfo =list.at(i);
            qDebug()<<fileinfo.fileName();
            if(str==fileinfo.fileName())
            {
                isdownload=false;
            }

        }
    }
    else //建立新的目录
    {
        dir.mkpath("download");
        qDebug()<<"make dir";
        isdownload=true;
    }


    if(isdownload)//如果尚未下载，则进行下载操作
    {
        QSqlQuery colquery("select * from blob_example");
        while(colquery.next())
        {
            if (url==colquery.value(0).toString())
            {

                qDebug()<<"正在下载"+colquery.value(0).toString();
                QString s =colquery.value(0).toString();
                QFileInfo info(s);
                QFile file(QDir::currentPath()+"/download/"+info.fileName());
                qDebug()<<QDir::currentPath()+"/download/"+info.fileName();
                if(!file.open(QIODevice::WriteOnly)){
                    qWarning("write error");
                }
                QByteArray imgBytes =colquery.value(1).toByteArray();
                QDataStream ds(&file);
                ds.writeRawData(imgBytes,imgBytes.size());
                file.close();
                if(ds.atEnd())
                {
                    QMessageBox::information(this,tr("提示"),tr("下载完成"));
                }
                break;
            }
        }

    }
    else
    {
        QMessageBox::information(this,tr("提示"),tr("您之前已下载过该文件"));
    }


}


