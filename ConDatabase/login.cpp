#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{

    setAutoFillBackground(true);
    setWindowFlags(Qt::FramelessWindowHint);//去除标题栏
    setMouseTracking(true);
    ui->setupUi(this);
    ui->usrEdit->setFocus();
    this->initSql();//初始化及创建数据库

}

Login::~Login()
{
    delete ui;
}

// 鼠标相对于窗体的位置
void Login::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        mMousePoint =e->globalPos()-this->pos();
        e->accept();
        mDragWindow =true;
    }
}

// 设置鼠标未被按下
void Login::mouseReleaseEvent(QMouseEvent *e)
{
    mDragWindow = false;
}

// 若鼠标左键被按下，移动窗体位置
void Login::mouseMoveEvent(QMouseEvent *e)
{
    if (mDragWindow && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mMousePoint);
        e->accept();
    }
}
void Login::initSql()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    if(!database.open())
    {
        qDebug()<<database.lastError();
        qFatal("failed to connect.") ;
    }
    else {
        qDebug()<<"open success";
        QSqlQuery sql_query; //改变量必须在成功打开数据库后定义才能有效
        sql_query.prepare("select tbl_name name from sqlite_master where type = 'table'");
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            QString tableName;
            while(sql_query.next())
            {
                tableName=sql_query.value(0).toString();
                qDebug()<<tableName;
                if(tableName.compare("userinfo"))
                {
                    tableFlag=false;
                    qDebug()<<"table is not exist";
                }
                else
                {
                    tableFlag=true;
                    qDebug()<<"table is exist";
                }
            }
        }
        if(tableFlag==false){
            sql_query.prepare("create table userinfo (id int primary key, name varchar(30), passwd varchar(30))");
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"table created";
            }
        }
    }
}
void Login::on_registerBtn_clicked()
{
    RegisterUser *reg =new RegisterUser();
    reg->show();
    //    transmitdb(database);
}
void Login::on_loginBtn_clicked()
{
    QSqlQuery sql_query;
    QString name =ui->usrEdit->text();
    qDebug()<<name;
    QString tempString ="select * from userinfo where name='"+name+"'";
    if(!sql_query.exec(tempString))
    {
        qDebug()<<sql_query.lastError();
        matchFlag=false;
    }
    else
    {
        while(sql_query.next())
        {
            usr_id=sql_query.value(0).toInt();
            usr_name=sql_query.value(1).toString();
            usr_passwd=sql_query.value(2).toString();
            qDebug()<<QString("id=%1    name=%2     passwd=%3  ").arg(usr_id).arg(usr_name).arg(usr_passwd);
        }
        if(usr_name==name) matchFlag=true;
        else  matchFlag=false;
    }
    if(matchFlag==false)
    {
        //用户名错误
        qDebug()<<"name invalid";
    }
    else
    {
        if(usr_passwd!=ui->pwdEdit->getPassword())
        {
            //密码错误
            qDebug()<<"passwd not match";
        }
        else
        {
            if(ui->usrEdit->text()==""||ui->pwdEdit->text()=="")
            {
                QMessageBox::information(this,"info","please input your username or password");
            }
            else
            {
                this->close();
                //用户名和密码均正确
                MainWindow *mw =new MainWindow();
//                QDesktopWidget *desktop =qApp->desktop();
//                mw->resize(870,600);
//                mw->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
                mw->showMaximized();


            }
        }
    }

}
