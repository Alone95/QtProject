#include "browser.h"
#include "ui_browser.h"
#include <QWebView>
#include <QLineEdit>

#include <QListWidget>
#include <QWebHistory>
Browser::Browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Browser)
{
    ui->setupUi(this);
    progress = 0;
    view = new QWebView(this);
    view->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    view->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    view->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    view->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,true);
    view->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);
    setCentralWidget(view);
//    resize(1000, 800);

    // 关联信号和槽
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
    connect(view, SIGNAL(titleChanged(QString)), this, SLOT(adjustTitle()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    connect(locationEdit, SIGNAL(returnPressed()), this, SLOT(changeLocation()));

    // 向工具栏添加动作和部件
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Back));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Forward));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Reload));
    ui->mainToolBar->addAction(view->pageAction(QWebPage::Stop));
    // 添加历史动作
    ui->mainToolBar->addAction(tr("历史"), this, SLOT(showHistory()));
    // 添加查找动作
    ui->mainToolBar->addAction(tr("查找"), this, SLOT(findText()));
    ui->mainToolBar->addWidget(locationEdit);

    // 设置并加载初始网页地址
    locationEdit->setText("http://www.baidu.com");
    view->load(QUrl("http://www.baidu.com"));

    // 必须先设置图标数据库路径
    view->settings()->setIconDatabasePath("./");
    connect(view, SIGNAL(iconChanged()), this, SLOT(changeIcon()));

    historyList = new QListWidget;
    historyList->setWindowTitle(tr("历史记录"));
    historyList->setMinimumWidth(300);
    connect(historyList, SIGNAL(clicked(QModelIndex)),
            this, SLOT(gotoHistory(QModelIndex)));

    view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(view->page(), SIGNAL(linkClicked(QUrl)),
            this, SLOT(urlChanged(QUrl)));
}

Browser::~Browser()
{
    delete ui;
    delete historyList;
}


// 改变路径
void Browser::changeLocation()
{
    QUrl url = QUrl(locationEdit->text());
    view->load(url);
    view->setFocus();

}

// 更新进度
void Browser::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

// 更新标题显示
void Browser::adjustTitle()
{
    if ( progress <= 0 || progress >= 100) {
        setWindowTitle(view->title());
    } else {
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
    }
}

// 加载完成后进行处理
void Browser::finishLoading(bool finished)
{
    if (finished) {
        progress = 100;
        setWindowTitle(view->title());
    } else {
        setWindowTitle("web page loading error!");
    }
}

// 更改网站图标
void Browser::changeIcon()
{
    setWindowIcon(view->icon());
}

// 显示历史记录
void Browser::showHistory()
{
    QList<QWebHistoryItem> list;
    list = view->history()->items();

    historyList->clear();
    foreach (QWebHistoryItem item, list) {
        QListWidgetItem *history = new QListWidgetItem(item.icon(), item.title());
        historyList->addItem(history);
    }
    historyList->show();
}

// 转到历史记录
void Browser::gotoHistory(QModelIndex index)
{
    QUrl url = view->history()->itemAt(index.row()).url();
    view->load(url);
}

// 点击超链接时进行跳转
void Browser::urlChanged(QUrl url)
{
    view->load(url);
    locationEdit->setText(url.toString());
}

// 查找字符串
void Browser::findText()
{
    view->page()->findText("yafeilinux", QWebPage::HighlightAllOccurrences);
}


