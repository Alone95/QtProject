#include "mainwindow.h"
#include "completelineedit.h"
#include "login.h"
#include "cmysplashscreen.h"
#include <QApplication>
#include<QStringList>
#include<QDebug>
#include<QTextCodec>
#include<QPixmap>
#include<QSplashScreen>
#include<QDateTime>
#include<QLabel>
#include<QMovie>
#include<QDesktopWidget>
#include <QTimer>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QPixmap pixmap(":/myImages/images/start_up.jpg");
    pixmap.scaled(QApplication::desktop()->availableGeometry().size(),Qt::KeepAspectRatio);

    CMySplashScreen *splash = new CMySplashScreen(pixmap,2000);
    splash->setDisabled(true);//禁用用户的输入事件响应
    splash->show();
    QTime t;
    t.start();
    while(t.elapsed() < 2000)// 延时2秒
    {
        a.processEvents();
    }
    Login log;
    log.show();
    return a.exec();

}


