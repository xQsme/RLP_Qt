#ifndef BEECOLONYTESTDIALOG_H
#define BEECOLONYTESTDIALOG_H

#include <QDialog>

namespace Ui {
class BeeColonyTestDialog;
}

class BeeColonyTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeeColonyTestDialog(QWidget *parent = 0);
    ~BeeColonyTestDialog();
    int getSelectStart();
    int getSelectEnd();
    int getSelectIncrement();
    int getBestStart();
    int getBestEnd();
    int getBestIncrement();
    int getChangeStart();
    int getChangeEnd();
    int getChangeIncrement();

private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::BeeColonyTestDialog *ui;
};

#endif // BEECOLONYTESTDIALOG_H
