#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class dialog : public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QWidget *parent = 0);
    
private slots:
    void on_pushButton_clicked();
signals:
    
public slots:

private:
    Ui::dialog *ui;
};

#endif // DIALOG_H
