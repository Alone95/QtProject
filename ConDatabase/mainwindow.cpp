#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "completelineedit.h"
#include <QPushButton>
#include <QMessageBox>
#include <QMargins>
#include <QLineEdit>
#include"workerthread.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initlayout();//初始化布局
    connect(cbo_sex, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(on_sel_sex(const QString &)));
    connect(edit, SIGNAL(returnPressed()), this, SLOT(search()));
    connect(pSearchButton,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(fileTreeview,SIGNAL(getText(QString)),this,SLOT(setText(QString)));

    //整合1
    mShowToolFile=false;
    mShowToolEdit=false;
    mShowToolAbout=false;
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

    //    sl=currentDir.entryList(QStringList("*"),QDir::Files|QDir::Dirs);
    //    QStringList sl = QStringList() << "Biao" << "Bin" << "Huang" << "Hua" << "Hello" << "BinBin" << "Hallo";
//    edit= new CompleteLineEdit;
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


    mUpLeftDock = new QDockWidget(tr("左上窗口"),this);
    mUpRightDock = new QDockWidget(tr("右上窗口"),this);
    mDownLeftDock = new QDockWidget(tr("左下窗口"),this);
    mDownRightDock = new QDockWidget(tr("右下窗口"),this);
    addDockWidget(Qt::LeftDockWidgetArea,mUpLeftDock);
    splitDockWidget(mUpLeftDock,mUpRightDock,Qt::Horizontal);
    splitDockWidget(mUpLeftDock,mDownLeftDock,Qt::Vertical);
    splitDockWidget(mUpRightDock,mDownRightDock,Qt::Vertical);
    mUpLeftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    mDownLeftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    mUpLeftDock->setMaximumWidth(300);
    mDownLeftDock->setMaximumWidth(300);
    mUpRightDock->setMinimumWidth(600);
    mDownRightDock->setMinimumWidth(600);

    fileTreeview =new FileTreeview();
    QVBoxLayout *vboxLayout= new QVBoxLayout();
    vboxLayout->addLayout(pSearchLayout);
    vboxLayout->addWidget(fileTreeview);

    QWidget *widget=new QWidget();
    widget->setLayout(vboxLayout);
    mUpLeftDock->setWidget(widget);

    dispdata =new Dispdata();
    mDownLeftDock->setWidget(dispdata);

    textEdit2 = new QTextEdit("右上侧");
    mUpRightDock->setWidget(textEdit2);

    textEdit3 = new QTextEdit("右下侧");
    mDownRightDock->setWidget(textEdit3);
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
    textEdit2->setText(string);
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
    this->addDockWidget(Qt::TopDockWidgetArea,mTopWidgetToolEdit);
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

void MainWindow::setDockMaximumSize()
{
    mText2->setMaximumSize(16777215, 16777215);
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
