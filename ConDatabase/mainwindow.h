/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDockWidget>
#include<QTreeWidget>
#include<QTextEdit>
#include<QTextCodec>
#include<QFileSystemModel>
#include<QTreeView>
#include<QDirModel>
#include <QSplitter>
#include <QTableWidget>
#include <QListWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "completelineedit.h"
#include "treeview.h"
#include"dispdata.h"
#include"filetreeview.h"
#include"workerthread.h"
#include<QMdiArea>
#include<QToolButton>
#include<QCompleter>
#include<QLabel>
#include"browser.h"
#include"xlsxdocument.h"
class SetToolBtn : public QToolButton
{
    Q_OBJECT
public:
    explicit SetToolBtn(QString background,QString toolTips,QWidget *parent = 0);

signals:



protected:
    //    void paintEvent(QPaintEvent *);
private:
    QPixmap normalPixmap;

};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //整合1
    void creatToolBars_File();
    void creatToolBars_Edit();
    void creatToolBars_About();
    void creatMainDcokWidget();
    void setToolBtnLayout_File();
    void setToolBtnLayout_Edit();
    void setToolBtnLayout_About();
    //    void setDockMaximumSize();

private slots:
    void on_sel_sex(const QString &text);
    void search();
    void setText(const QString&string);
    void timerUpDate();
    //    void finishThread(const QStringList&stringlist);

    void slot_writeToExcel();
    //整合1
    void on_action_Tool_File_triggered();

    void on_action_Tool_Edit_triggered();

    void on_action_Tool_About_triggered();

signals:
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
private:
    Ui::MainWindow *ui;
    void initlayout();
    void listAll(const QString &index);
    QFileInfoList getFileList(const QString&path);
private:
    WorkerThread *mWorkerthread;
    QStringList mStringlist;
    //    TreeView    *mTreeView;
    QDockWidget *mcenter;
    QDockWidget *mUpLeftDock;
    QDockWidget *mDownLeftDock;

    QDockWidget *mUpRightDock;
    QDockWidget *mDownRightDock;
    QDockWidget *mBottomDock;
    QTreeView *mTreeWidge;
    QTableWidget *m_table;
    QSplitter *m_spliter;
    QListWidget *m_list;
    QTableWidget *m_uptable;
    QListWidget *m_uplist;
    QComboBox *cbo_sex;
    QHBoxLayout *hLayout;
    QPushButton *pSearchButton;
    //    CompleteLineEdit *edit;
    QLineEdit *edit;
    QCompleter *completer;
    QDirModel * model ;
    QHBoxLayout *pcbosex_Layout;
    FileTreeview * fileTreeview;
    Dispdata *dispdata;

    QTableWidget *m_excelWidget;
    QPushButton * m_excelBtn;

    //整合1
    QDockWidget *mTopWidgetToolFile;
    QDockWidget *mTopWidgetToolEdit;
    QDockWidget *mTopWidgetToolAbout;

    QDockWidget *mTenterWidget;
    QDockWidget *mTeftWidgetTop;
    QDockWidget *mTeftWidgetDown;

    QStatusBar *mTtatusBar;

    QTextEdit *mText2;
    QTextEdit *mTextCenter;
    QTextEdit *mTextToolFile;
    QTextEdit *mTextToolEdit;
    QTextEdit *mTextToolAbout;
    QTextEdit *textEdit2;
    QTextEdit *textEdit3;
    QLabel *hint_label;
    QLabel *time_label;
    QMdiArea *mdiarea;

    QLineEdit *mSearchLineEdit;
    //SearchButton *m_searchButton;

    SetToolBtn *mNewFileBtn;
    SetToolBtn *mOpenFileBtn;
    SetToolBtn *mCloseBtn;
    SetToolBtn *mSaveBtn;
    SetToolBtn *mSaveAsBtn;
    SetToolBtn *mPrintBtn;
    SetToolBtn *mQuitBtn;

    SetToolBtn *mUndoBtn;
    SetToolBtn *mCutBtn;
    SetToolBtn *mCopyBtn;
    SetToolBtn *mPastBtn;
    SetToolBtn *mFindBtn;

    SetToolBtn *mAboutBtn;

    QHBoxLayout *mHlayoutToolFile;
    QHBoxLayout *mHlayoutToolEdit;
    QHBoxLayout *mHlayoutToolAbout;

    bool mShowToolFile;
    bool mShowToolEdit;
    bool mShowToolAbout;
};

#endif // MAINWINDOW_H
