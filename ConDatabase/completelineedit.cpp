#include "CompleteLineEdit.h"
#include "mainwindow.h"
#include <QKeyEvent>
#include <QtGui>
#include <QListView>
#include <QtGui>
#include<QStringListModel>
#include <QDebug>


CompleteLineEdit::CompleteLineEdit( QWidget *parent)
    : QLineEdit(parent)
{
    workerthread =new WorkerThread;
    workerthread->start();
    listView = new QListView(this);//下拉列表
    model = new QStringListModel(this);
    listView->setWindowFlags(Qt::ToolTip);//
    connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(setCompleter(const QString &)));
    connect(listView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));
    connect(workerthread,SIGNAL(sendStringlist(QStringList)),this,SLOT(getStringList(QStringList)));
}

void CompleteLineEdit::getStringList(const QStringList &stringlist)
{
    words=stringlist;
    qDebug()<<"words's length="<<words.size();
}

void CompleteLineEdit::focusOutEvent(QFocusEvent *e) {
    listView->hide();
}

void CompleteLineEdit::keyPressEvent(QKeyEvent *e) {
    if (!listView->isHidden())
    {
        int key = e->key();
        int count = listView->model()->rowCount();
        QModelIndex currentIndex = listView->currentIndex();

        if (Qt::Key_Down == key)
        {
            // 按向下方向键时，移动光标选中下一个完成列表中的项
            int row = currentIndex.row() + 1;
            if (row >= count)
            {
                row = 0;
            }

            QModelIndex index = listView->model()->index(row, 0);
            listView->setCurrentIndex(index);
        } else if (Qt::Key_Up == key) {
            // 按向下方向键时，移动光标选中上一个完成列表中的项
            int row = currentIndex.row() - 1;
            if (row < 0) {
                row = count - 1;
            }

            QModelIndex index = listView->model()->index(row, 0);
            listView->setCurrentIndex(index);
        } else if (Qt::Key_Escape == key) {
            // 按下Esc键时，隐藏完成列表
            listView->hide();
        }
        else if (Qt::Key_Enter == key || Qt::Key_Return == key)
        {
            // 按下回车键时，使用完成列表中选中的项，并隐藏完成列表
            if (currentIndex.isValid())
            {
                QString text = listView->currentIndex().data().toString();
                setText(text);
            }

            listView->hide();
        } else {
            // 其他情况，隐藏完成列表，并使用QLineEdit的键盘按下事件
            listView->hide();
            QLineEdit::keyPressEvent(e);
        }
    } else {
        QLineEdit::keyPressEvent(e);
    }
}

void CompleteLineEdit::setCompleter(const QString &text) {
    if (text.isEmpty()) {
        listView->hide();
        return;
    }

    if ((text.length() > 1) && (!listView->isHidden())) {
        return;
    }

    // 如果完整的完成列表中的某个单词包含输入的文本，则加入要显示的完成列表串中
    QStringList sl;
    foreach(QString word, words)
    {//逐个输出words中的元素到word中
        if (word.contains(text))
        {//这个的意思是如果输入的单词或者字母包含在word中则将他们输入到s1中
            sl << word;
        }
    }


    model->setStringList(sl);//将s1加载到模型里面
    listView->setModel(model);//将模型弄到显示表里面

    if (model->rowCount() == 0) {
        return;
    }

    // 下拉列表的位置
    listView->setMinimumWidth(width());
    listView->setMaximumWidth(width());

    QPoint p(0, height());//将listView右下角作为下拉列表的坐标体系
    int x = mapToGlobal(p).x();
    int y = mapToGlobal(p).y() + 1;

    listView->move(x, y);
    listView->setFocus();
    listView->show();

}

void CompleteLineEdit::completeText(const QModelIndex &index) {
    QString text = index.data().toString();
    setText(text);
    listView->hide();
}

