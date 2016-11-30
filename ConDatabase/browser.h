/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>

class QWebView;
class QLineEdit;

#include <QModelIndex>
class QListWidget;

#include <QUrl>
namespace Ui {
class Browser;
}

class Browser : public QMainWindow
{
    Q_OBJECT

public:
    explicit Browser(QWidget *parent = 0);
    ~Browser();

private:
    Ui::Browser *ui;
    QWebView *view;
    QLineEdit *locationEdit;
    int progress;

    QListWidget *historyList;
protected slots:
    void changeLocation(); // 改变路径
    void setProgress(int); // 更新进度
    void adjustTitle();    // 更新标题显示
    void finishLoading(bool); // 加载完成后进行处理
    void changeIcon(); // 更改网站图标

    void showHistory(); // 显示历史记录
    void gotoHistory(QModelIndex); // 转到历史记录

    void urlChanged(QUrl); // 点击超链接时进行跳转
    void findText(); // 查找字符串
};

#endif // BROWSER_H
