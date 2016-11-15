#include "registeruser.h"
#include "ui_registeruser.h"
#include<QTextCodec>
RegisterUser::RegisterUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterUser)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowModality(Qt::ApplicationModal);
    ui->setupUi(this);
}

RegisterUser::~RegisterUser()
{
    delete ui;
}

void RegisterUser::judge_input()
{
    nameflag =false;
    passwdflag =false;

    if(ui->usrEdit->text()=="")
    {
        nameflag=false;
        QMessageBox::information(this,tr("info"),tr("Username can not be empty!"));

    }

    else if(ui->pwdEdit->getPassword()==""||ui->confirmEdit->getPassword()=="")
    {
        passwdflag=false;
        QMessageBox::information(this,tr("info"),tr("Password can not be empty!"));

    }
    else if(ui->pwdEdit->getPassword()==ui->confirmEdit->getPassword())
    {
        passwdflag=true;
    }
    else if(!(ui->pwdEdit->getPassword()==ui->confirmEdit->getPassword()))
    {
        passwdflag=false;
        QMessageBox::information(this,tr("info"),tr("The passwords you entered must be the same!"));

    }
    else
    {
        qDebug()<<"passwd error";
        passwdflag=false;
    }



}
void RegisterUser::select_maxid()
{
    QSqlQuery select_maxid;
    select_maxid.prepare("select max(id) from userinfo");
    if(!select_maxid.exec()){
        qDebug()<<select_maxid.lastError();
    }
    else
    {
        while(select_maxid.next())
        {
            max_id=select_maxid.value(0).toInt();
            qDebug()<<QString("max id:%1").arg(max_id);
        }
    }
}

void RegisterUser::select_data()
{
    QSqlQuery sql_query;

    //查询部分数据
    if(!sql_query.exec("select name from userinfo"))
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(1)
        {
            if(sql_query.next())//name有数据
            {
                QString name =sql_query.value(0).toString();
                qDebug()<<name;

                if(ui->usrEdit->text()==name)//用户名已经存在
                {
                    qDebug()<<"name existed";
                    nameflag=false;
                    QMessageBox::information(this,tr("info"),QObject::tr("Username already exists"));
                    break;
                }
                else
                {
                    nameflag=true;
                }
            }
            else
            {
                //name列为空
                nameflag=true;
                break;
            }
        }
    }
    newid=max_id+1;
    if(nameflag) newname=ui->usrEdit->text();

    if(passwdflag) newpasswd=ui->pwdEdit->getPassword();


}

void RegisterUser::insert_data()
{
    QSqlQuery sql_query;

    if(nameflag&&passwdflag)
    {
        sql_query.prepare("insert into userinfo values (?, ?, ?)");
        sql_query.addBindValue(newid);
        sql_query.addBindValue(newname);
        sql_query.addBindValue(newpasswd);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();

        }
        else
        {
            qDebug()<<"inserted";
            QMessageBox::information(this,tr("info"),tr("Registered Successfully!"));
            this->close();
        }
    }

}

void RegisterUser::on_regBtn_clicked()
{
    judge_input();
    select_maxid();
    select_data();
    insert_data();
}



