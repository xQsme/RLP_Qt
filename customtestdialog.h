#ifndef CUSTOMTESTDIALOG_H
#define CUSTOMTESTDIALOG_H

#include <QDialog>

namespace Ui {
class CustomTestDialog;
}

class CustomTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTestDialog(QWidget *parent = 0);
    ~CustomTestDialog();
    int getStartElitism();
    int getEndElitism();
    int getIncrementElitism();
    int getStartMutation();
    int getEndMutation();
    int getIncrementMutation();

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::CustomTestDialog *ui;
};

#endif // CUSTOMTESTDIALOG_H
