/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/
#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include<QString>
#include<QMouseEvent>
#include<QImage>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
#include"registeruser.h"
#include "ui_registeruser.h"
#include"mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    Ui::Login *ui;

    void initSql();
private slots:


    void on_registerBtn_clicked();

    void on_loginBtn_clicked();



private:
   
    QPoint mMousePoint;
    bool  mDragWindow;
    QSqlDatabase database;
    bool tableFlag;
    int usr_id;
    QString usr_passwd;
    QString usr_name;
    bool matchFlag;
    QString select_table ;
    QString create_sql ;
    QString insert_sql  ;
    QString select_max_sql;
    QString select_sql  ;

};

#endif // LOGIN_H


