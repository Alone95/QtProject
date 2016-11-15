/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/

#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QWidget>
#include<QSqlDatabase>
#include<QString>
#include<QMessageBox>
#include"login.h"
namespace Ui {
class RegisterUser;
}

class RegisterUser : public QWidget
{
    Q_OBJECT
    
public:
    explicit RegisterUser(QWidget *parent = 0);
    ~RegisterUser();
    

private slots:

;

    void on_regBtn_clicked();
private:
    void judge_input();
    void select_maxid();
    void select_data();
    void insert_data();

private:
    Ui::RegisterUser *ui;
    QSqlDatabase database;
    bool tableFlag;
    int max_id;
    bool nameflag ;
    bool passwdflag ;
    int newid;
    QString newname;
    QString newpasswd;
};

#endif // REGISTERUSER_H
