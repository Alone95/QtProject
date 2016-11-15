
/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef DISPDATA_H
#define DISPDATA_H
#include<QListWidget>
#include<QSqlQuery>
#include<QTime>
#include<QSqlDatabase>
#include<QSqlError>
#include<QDir>
#include<QTextCodec>
#include<QDebug>
#include<QTextEdit>
#include<QMenu>
#include<QMessageBox>
#include<QMouseEvent>
#include<QString>
#include<QByteArray>
#include<QDataStream>
#include<QFile>
#include<QFileInfo>
#include<QProgressBar>
#include<QAction>
#include<QFileDialog>
#include<QTimer>
#include<QVector>
#include<QScrollArea>
class Dispdata : public QListWidget
{
    Q_OBJECT

public:
    explicit Dispdata(QListWidget *parent=0);
    ~Dispdata();

private:
    QSqlDatabase db ;
    QTimer *clickedTimer;
    QListWidgetItem *listWidgetItem;
    bool isDouble;
    int TimerColumn;
//    bool *isdownload;
private:
    void display();
    void connsql();
    void judge_filetype(const QString&filename);
private slots:
    void add_data();
    void del_data();
    void upd_data();
    void down_data();
    void handleTransfer(QListWidgetItem *item);
    void handleListWidgetSingleClick();
    void handleListWidgetDoubleClick();
    QString changed();
protected:
//    void mousePressEvent(QMouseEvent *event);
//    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);//右键点击
    void keyPressEvent(QKeyEvent *event);

};

#endif // DISPDATA_H
