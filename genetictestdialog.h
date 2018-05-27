#ifndef GENETICTESTDIALOG_H
#define GENETICTESTDIALOG_H

#include <QDialog>

namespace Ui {
class GeneticTestDialog;
}

class GeneticTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneticTestDialog(QWidget *parent = 0);
    ~GeneticTestDialog();
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
    Ui::GeneticTestDialog *ui;
};

#endif // GENETICTESTDIALOG_H
