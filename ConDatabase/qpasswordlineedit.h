/****************************************************************************
**
** Copyright (C) 2016 Alone95
** Version	: 0.1.0
** Author	: Alone95
** Website	: https://github.com/Alone95
**
****************************************************************************/

#ifndef QPASSWORDLINEEDIT_H
#define QPASSWORDLINEEDIT_H
#include <QLineEdit>
/*
  * 类的说明：
  * 类的参数：
  * 类的返回值：
  * 修改时间：
  * 创建者：
  * 联系方式：
   */
class QPasswordLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    //默认输入300毫秒后消失
    QPasswordLineEdit(QWidget *parent,int timeout = 300);
    ~QPasswordLineEdit();

    //获取真实的密码
    QString getPassword();
    //设置显示到隐藏的时间间隔
    void setTimeout(int msec);

private slots:
    void slotCursorPositionChanged(int,int);
    void slotTextEdited(const QString&);
    //显示隐藏后的密码
    void slotDisplayMaskPassword();

private:
    //获取隐藏后的密码，这里为星号
    QString  getMaskPassword();

private:
    int	mTimeout;
    QString	mLineEditText;
    //到最后一个字符的长度
    int	mLastCharCount;
};

#endif // QPASSWORDLINEEDIT_H
