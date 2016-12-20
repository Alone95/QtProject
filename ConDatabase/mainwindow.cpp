#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "completelineedit.h"
#include <QPushButton>
#include <QMessageBox>
#include <QMargins>
#include <QLineEdit>
#include<QDragEnterEvent>
#include<QUrl>
#include<QTextStream>
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    initlayout();//初始化布局

    connect(cbo_sex, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_sel_sex(const QString &)));
    connect(edit, SIGNAL(returnPressed()), this, SLOT(search()));
    connect(pSearchButton,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(fileTreeview,SIGNAL(getText(QString)),this,SLOT(setText(QString)));

    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));//关联定时器计满信号和相应的槽函数
    timer->start(1000);//定时器开始计时，其中1000表示1000ms即1秒

    //整合1
    mShowToolFile=false;
    mShowToolEdit=false;
    mShowToolAbout=false;
    mediaplayer =new QMediaPlayer();
}


MainWindow::~MainWindow()
{
    delete ui;
}




QFileInfoList MainWindow::getFileList(const QString&path)
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
        mStringlist.append(fileinfo.filePath());
    }
    return file_list;
}


void MainWindow::initlayout()
{
    cbo_sex = new QComboBox();
    cbo_sex->addItem(QWidget::tr("本地文件"));
    cbo_sex->addItem(QWidget::tr("数据库文件"));

    edit=new QLineEdit;
    completer =new QCompleter;
    model =new QDirModel;
    completer->setModel(model);
    edit->setCompleter(completer);
    pSearchButton=  new QPushButton();
    pSearchButton->setCursor(Qt::PointingHandCursor);
    pSearchButton->setFixedSize(22, 22);
    pSearchButton->setToolTip(tr("search"));
    pSearchButton->setStyleSheet("QPushButton{border-image:url(:/myImages/icon_search_normal.png); background:transparent;} \
                                 QPushButton:hover{border-image:url(:/myImages/icon_search_hover.png)} \
                                 QPushButton:pressed{border-image:url(:/myImages/icon_search_press.png)}");

    QMargins margins =edit->textMargins();
    edit->setTextMargins(margins.left(),margins.top(),pSearchButton->width(),margins.bottom());
    edit->setPlaceholderText("请输入搜索内容");
    QHBoxLayout *pSearchLayout2= new QHBoxLayout();
    pSearchLayout2->addStretch();
    pSearchLayout2->addWidget(pSearchButton);
    pSearchLayout2->setSpacing(0);
    pSearchLayout2->setContentsMargins(0, 0, 0, 0);
    edit->setLayout(pSearchLayout2);
    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->setSpacing(10);
    pSearchLayout->addWidget(cbo_sex);
    pSearchLayout->addWidget(edit);

    mUpLeftDock = new QDockWidget(tr("我的电脑"),this);
    mUpRightDock = new QDockWidget(tr("文本编辑器"),this);
    mDownLeftDock = new QDockWidget(tr("数据库"),this);
    mDownRightDock = new QDockWidget(tr("浏览器"),this);


    setCentralWidget(mUpLeftDock);
    addDockWidget(Qt::LeftDockWidgetArea,mUpLeftDock);
    splitDockWidget(mUpLeftDock,mUpRightDock,Qt::Horizontal);
    splitDockWidget(mUpLeftDock,mDownLeftDock,Qt::Vertical);

    tabifyDockWidget(mUpRightDock,mDownRightDock);
    mUpLeftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mDownLeftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mUpRightDock->raise();
    mUpLeftDock->setMinimumWidth(250);
    mDownLeftDock->setMinimumWidth(250);
    mUpLeftDock->setMaximumWidth(250);
    mDownLeftDock->setMaximumWidth(250);



    fileTreeview =new FileTreeview();
    QVBoxLayout *vboxLayout= new QVBoxLayout();
    vboxLayout->addLayout(pSearchLayout);
    vboxLayout->addWidget(fileTreeview);
    //FileView
    QWidget *widget=new QWidget();
    widget->setLayout(vboxLayout);
    mUpLeftDock->setWidget(widget);
    //Database
    dispdata =new Dispdata();
    mDownLeftDock->setWidget(dispdata);

    //Excel
//    QWidget *upleftwidget =new QWidget(this);
//    QHBoxLayout *hlayout =new QHBoxLayout();
//    QVBoxLayout *vlayout =new QVBoxLayout();
//    QXlsx::Document xlsx("G:/计算机14-01.xlsx");
//    QXlsx::CellRange range=xlsx.dimension();
//    int rowcount=range.rowCount();
//    int columncount= range.columnCount();
//    qDebug()<<rowcount<<columncount;
//    m_excelWidget =new QTableWidget();
//    m_excelBtn=new QPushButton("生成excel");
//    connect(m_excelBtn,SIGNAL(clicked()),this,SLOT(slot_writeToExcel()));

//    hlayout->addStretch(10);
//    hlayout->addWidget(m_excelBtn);

//    vlayout->addWidget(m_excelWidget);
//    vlayout->addLayout(hlayout);
//    upleftwidget->setLayout(vlayout);
//    m_excelWidget->setRowCount(rowcount);
//    m_excelWidget->setColumnCount(columncount);
//    for(int i=0;i<rowcount;i++){
//        for(int j=0;j<columncount;j++){

//            QTableWidgetItem *item =new QTableWidgetItem(xlsx.read(i,j).toString());
//            item->setTextAlignment(Qt::AlignCenter);
//            m_excelWidget->setItem(i,j,item);
//        }
//    }
//    m_excelWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
//    m_excelWidget->setEditTriggers(QHeaderView::DoubleClicked);
//    m_excelWidget->setSelectionBehavior(QHeaderView::SelectRows);
//    m_excelWidget->horizontalHeader()->setVisible(true);
//    m_excelWidget->verticalHeader()->setVisible(true);
    mdiarea =new QMdiArea();
    mdiarea->setViewMode(QMdiArea::TabbedView);
    mdiarea->setTabPosition(QTabWidget::North);
    mdiarea->setTabsClosable(true);
    mdiarea->setTabsMovable(true);
    mdiarea->setTabShape(QTabWidget::Triangular);
    mUpRightDock->setWidget(mdiarea);

    //Browser
    Browser *browser =new Browser();
    mDownRightDock->setWidget(browser);

    hint_label= new QLabel();
    time_label= new QLabel();
    time_label->setMinimumSize(time_label->sizeHint());
    time_label->setAlignment(Qt::AlignCenter);
    hint_label->setText(tr("欢迎使用"));
    ui->statusBar->addWidget(hint_label,1);
    ui->statusBar->addWidget(time_label,0);
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border:0px}"));//去掉label的边框.

}

void MainWindow::slot_writeToExcel()
{
    QXlsx::Document xlsx;
    int rows =m_excelWidget->rowCount();
    int cols= m_excelWidget->columnCount();
    QString text;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            text= m_excelWidget->item(i,j)->text();
            xlsx.write(i+1,j+1,text);
        }
    }
    xlsx.saveAs("G:/副本.xlsx");
}

void MainWindow::timerUpDate()//定时器更新时间的显示
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");//设置系统时间显示格式
    time_label->setText(str); //在标签上显示时间

}


void MainWindow::on_sel_sex(const QString &text)
{
    QString str;
    str = "You select " + text;
    QMessageBox::information(this, tr("Info"), str);
}

void MainWindow::search()
{
    QString strText = edit->text();
    if (!strText.isEmpty())
    {
        QMessageBox::information(this, "搜索", tr("搜索内容为%1").arg(strText));
    }
}

void MainWindow::setText(const QString &string)
{
    QString suffix =string.section(".",-1,-1);
    QTextEdit * textedit =new QTextEdit();

    QFile file(string);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly)) return;

    if(suffix=="txt"||suffix=="ini"||suffix=="log"||suffix=="java"||suffix=="sql"||suffix=="xml")
    {
         QMdiSubWindow *child = mdiarea->addSubWindow(textedit);
         textedit->setText(in.readAll());
         child->setWindowTitle(string);
         child->show();
    }
    else if(suffix=="h"||suffix=="cpp"||suffix=="py")
    {
         QMdiSubWindow *child = mdiarea->addSubWindow(textedit);
         in.setCodec("utf-8");
         textedit->setText(in.readAll());
         child->setWindowTitle(string);
         child->show();
    }
    else if(suffix=="jpg"||suffix=="png")
    {
        QImage image(string);
        QLabel *label =new QLabel();
        image=image.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        label->setPixmap(QPixmap::fromImage(image));
        label->setAlignment(Qt::AlignCenter);
        QMdiSubWindow *child = mdiarea->addSubWindow(label);
        child->setWindowTitle(string);
        child->show();
    }
    else if(suffix=="gif")
    {

        QLabel *label =new QLabel();
        QMovie *movie =new QMovie(string);
        label->setMovie(movie);
        label->setAlignment(Qt::AlignCenter);
        QMdiSubWindow *child =mdiarea->addSubWindow(label);
        child->setWindowTitle(string);
        child->show();
        movie->start();

    }
    else if(suffix=="mp3"||suffix=="wma")
    {

        mediaplayer->stop();
        mediaplayer->setMedia(QUrl::fromLocalFile(string));
        mediaplayer->play();
        QMessageBox::information(this,"正在播放",string);
    }
    else
        return;


}




//整合1
void MainWindow::creatToolBars_File()
{
    //设置工具栏的位置
    mTopWidgetToolFile=new QDockWidget();
    mTopWidgetToolFile->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mTextToolFile=new QTextEdit;
    mTextToolFile->setReadOnly(true);
    mTopWidgetToolFile->setWidget(mTextToolFile);
    QWidget *noTitleBarToolFile=new QWidget;
    mTopWidgetToolFile->setTitleBarWidget(noTitleBarToolFile);
    mTopWidgetToolFile->setMaximumHeight(40);
    //    m_topWidget_Tool_File->setMaximumWidth(250);
    this->addDockWidget(Qt::TopDockWidgetArea,mTopWidgetToolFile);

    //Tool_File_Btn
    mNewFileBtn=new SetToolBtn(":/myImages/images/document-icon.png",tr("新建"),mTextToolFile);
    mOpenFileBtn=new SetToolBtn(":/myImages/images/folder-icon.png",tr("打开"),mTextToolFile);
    mCloseBtn=new SetToolBtn(":/myImages/images/power-icon.png",tr("关闭"),mTextToolFile);
    mSaveBtn=new SetToolBtn(":/myImages/images/memorycard-icon.png",tr("保存"),mTextToolFile);
    mSaveAsBtn=new SetToolBtn(":/myImages/images/frames-icon.png",tr("另存为"),mTextToolFile);
    mPrintBtn=new SetToolBtn(":/myImages/images/Polaroid-icon.png",tr("打印"),mTextToolFile);
    mQuitBtn=new SetToolBtn(":/myImages/images/running-icon.png",tr("退出"),mTextToolFile);

}

void MainWindow::creatToolBars_Edit()
{
    mTopWidgetToolEdit=new QDockWidget();
    mTopWidgetToolEdit->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mTextToolEdit=new QTextEdit;
    mTextToolEdit->setReadOnly(true);
    mTopWidgetToolEdit->setWidget(mTextToolEdit);
    QWidget *noTitleBarToolEdit=new QWidget;
    mTopWidgetToolEdit->setTitleBarWidget(noTitleBarToolEdit);
    mTopWidgetToolEdit->setMaximumHeight(40);
    addDockWidget(Qt::TopDockWidgetArea,mTopWidgetToolEdit);



    //Tool_Edit_Btn
    mUndoBtn=new SetToolBtn(":/myImages/images/undo.png",tr("撤销"),mTextToolEdit);
    mCutBtn=new SetToolBtn(":/myImages/images/cut.png",tr("剪切"),mTextToolEdit);
    mCopyBtn=new SetToolBtn(":/myImages/images/copy.png",tr("复制"),mTextToolEdit);
    mPastBtn=new SetToolBtn(":/myImages/images/past.png",tr("粘贴"),mTextToolEdit);
    mFindBtn=new SetToolBtn(":/myImages/images/magnifying-glass-icon.png",tr("查找"),mTextToolEdit);
}

void MainWindow::creatToolBars_About()
{
    mTopWidgetToolAbout=new QDockWidget;
    mTopWidgetToolAbout->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mTextToolAbout=new QTextEdit;
    mTextToolAbout->setReadOnly(true);
    mTopWidgetToolAbout->setWidget(mTextToolAbout);
    QWidget *noTitleBarToolAbout=new QWidget;
    mTopWidgetToolAbout->setTitleBarWidget(noTitleBarToolAbout);
    mTopWidgetToolAbout->setMaximumHeight(40);
    this->addDockWidget(Qt::TopDockWidgetArea,mTopWidgetToolAbout);

    mAboutBtn=new SetToolBtn(":/myImages/images/about.png",tr("关于"),mTextToolAbout);

}
void MainWindow::setToolBtnLayout_File()
{
    mHlayoutToolFile=new QHBoxLayout;
    mHlayoutToolFile->addWidget(mNewFileBtn);
    mHlayoutToolFile->addWidget(mOpenFileBtn);
    mHlayoutToolFile->addWidget(mCloseBtn);
    mHlayoutToolFile->addWidget(mSaveBtn);
    mHlayoutToolFile->addWidget(mSaveAsBtn);
    mHlayoutToolFile->addWidget(mPrintBtn);
    mHlayoutToolFile->addWidget(mQuitBtn,0,Qt::AlignLeft);
    mHlayoutToolFile->setSpacing(10);
    mHlayoutToolFile->setContentsMargins(3,0,3,0);
    mTextToolFile->setLayout(mHlayoutToolFile);
}

void MainWindow::setToolBtnLayout_Edit()
{
    mHlayoutToolEdit=new QHBoxLayout;
    mHlayoutToolEdit->addWidget(mUndoBtn);
    mHlayoutToolEdit->addWidget(mCutBtn);
    mHlayoutToolEdit->addWidget(mCopyBtn);
    mHlayoutToolEdit->addWidget(mPastBtn);
    mHlayoutToolEdit->addWidget(mFindBtn,0,Qt::AlignLeft);
    mHlayoutToolEdit->setSpacing(20);
    mHlayoutToolEdit->setContentsMargins(3,0,0,0);
    mTextToolEdit->setLayout(mHlayoutToolEdit);
}

void MainWindow::setToolBtnLayout_About()
{
    mHlayoutToolAbout=new QHBoxLayout;
    mHlayoutToolAbout->addWidget(mAboutBtn,0,Qt::AlignLeft);
    mHlayoutToolAbout->setContentsMargins(3,0,0,0);
    mTextToolAbout->setLayout(mHlayoutToolAbout);
}


void MainWindow::on_action_Tool_File_triggered()
{
    if(!mShowToolFile)
    {
        if(mShowToolEdit==true)
        {
            mTopWidgetToolEdit->hide();
            mShowToolEdit=false;
        }
        if(mShowToolAbout)
        {
            mTopWidgetToolAbout->hide();
            mShowToolAbout=false;
        }
        creatToolBars_File();
        setToolBtnLayout_File();
        mShowToolFile=true;


    }

}

void MainWindow::on_action_Tool_Edit_triggered()
{
    if(!mShowToolEdit)
    {
        if(mShowToolFile==true)
        {
            mTopWidgetToolFile->hide();
            mShowToolFile=false;
        }
        if(mShowToolAbout==true)
        {
            mTopWidgetToolAbout->hide();
            mShowToolAbout=false;
        }
        creatToolBars_Edit();
        setToolBtnLayout_Edit();
        mShowToolEdit=true;
    }
}

void MainWindow::on_action_Tool_About_triggered()
{
    if(!mShowToolAbout)
    {
        if(mShowToolFile==true)
        {
            mTopWidgetToolFile->hide();
            mShowToolFile=false;
        }
        if(mShowToolEdit)
        {
            mTopWidgetToolEdit->hide();
            mShowToolEdit=false;
        }
        creatToolBars_About();
        setToolBtnLayout_About();
        mShowToolAbout=true;


    }
}
SetToolBtn::SetToolBtn(QString background, QString toolTips,QWidget *parent):
    QToolButton(parent)
{
    //    normalPixmap.load(background);
    this->setIcon(QIcon(background));
    this->setIconSize(QSize(30,30));
    this->setFixedSize(30,30);
    this->setAutoRaise(true);
    this->setToolTip(toolTips);
    this->setContentsMargins(0,0,0,0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData =event->mimeData();
    if(mimeData->hasUrls()){

        QList<QUrl>urllist =mimeData->urls();
        if(urllist.isEmpty()) return;

        foreach (QUrl url, urllist)
        {
            QString fileName =url.toLocalFile();
            qDebug()<<fileName;
            if(!fileName.isEmpty())
            {
                QFile file(fileName);
                QString suffix =fileName.section(".",-1,-1);
                QTextEdit * textedit =new QTextEdit();
                QTextStream in(&file);
                if(!file.open(QIODevice::ReadOnly))return;

                if(suffix=="txt"||suffix=="ini"||suffix=="log"||suffix=="java"||suffix=="sql"||suffix=="xml")
                {
                    QMdiSubWindow *child = mdiarea->addSubWindow(textedit);
                    textedit->setText(in.readAll());
                    child->setWindowTitle(fileName);
                    child->show();
                }
                else if(suffix=="h"||suffix=="cpp"||suffix=="py")
                {
                    QMdiSubWindow *child = mdiarea->addSubWindow(textedit);
                    in.setCodec("utf-8");
                    textedit->setText(in.readAll());
                    child->setWindowTitle(fileName);
                    child->show();
                }
                else if(suffix=="jpg"||suffix=="png")
                {

                    QImage image(fileName);
                    QLabel *label =new QLabel();
                    image=image.scaled(label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                    label->setPixmap(QPixmap::fromImage(image));
                    label->setAlignment(Qt::AlignCenter);
                    QMdiSubWindow *child = mdiarea->addSubWindow(label);
                    child->setWindowTitle(fileName);
                    child->show();

                }
                else if(suffix=="gif")
                {
                    qDebug()<<suffix;
                    QLabel *label =new QLabel();
                    QMovie *movie =new QMovie(fileName);
                    label->setMovie(movie);
                    label->setAlignment(Qt::AlignCenter);
                    QMdiSubWindow *child =mdiarea->addSubWindow(label);
                    child->setWindowTitle(fileName);
                    child->show();
                    movie->start();

                }
                else if(suffix=="mp3"||suffix=="wma")
                {
                    mediaplayer->stop();
                    mediaplayer->setMedia(QUrl::fromLocalFile(fileName));
                    mediaplayer->play();
                    QMessageBox::information(this,"正在播放",fileName);
                }

                else
                    return;

            }
        }
    }

}


