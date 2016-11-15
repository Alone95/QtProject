#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include<QTextCodec>
#include<QPalette>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)

{
     QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    ui->setupUi(this);

   setWindowFlags( (Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint));
//    ui->usrLineEdit->setPlaceholderText(tr("请输入用户名"));
//    ui->pwdlineEdit->setPlaceholderText(tr("请输入密码"));
//    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
//    //设置背景颜色
//    QPalette palette =this->palette();
//    palette.setColor(QPalette::Window,QColor(125,125,125));
//    this->setPalette(palette);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
//    if(ui->usrLineEdit->text()==tr("admin")&&ui->pwdlineEdit->text()==tr("123456"))
//    {
//         accept();
//    }
//    else{
//        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),
//                           QMessageBox::Yes);
//    }
}
