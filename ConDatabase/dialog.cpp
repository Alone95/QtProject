#include "dialog.h"
#include <QTGui>
#include <QCompleter>
#include <QStringList>
#include <QPushButton>
#include <QGridLayout>
#include "completelineedit.h"
#include "mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

dialog::dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog)
{
//    QStringList sl = QStringList() << "Biao" << "Bin" << "Huang" << "Hua" << "Hello" << "BinBin" << "Hallo";
//    CompleteLineEdit * edit= new CompleteLineEdit(sl);
//    QPushButton *button = new QPushButton("Button");
//    QGridLayout *layout = new QGridLayout();
//    button->resize(3,3);
//    layout->addWidget(edit,0,0,5,3);
//    layout->addWidget(button,5,0,3,3);
//    this->setLayout(layout);
    MainWindow.initlayout();
    CompleteLineEdit e(sl);
    e.show();
}
