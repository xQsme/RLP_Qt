#ifndef ANTCOLONYTESTDIALOG_H
#define ANTCOLONYTESTDIALOG_H

#include <QDialog>

namespace Ui {
class AntColonyTestDialog;
}

class AntColonyTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AntColonyTestDialog(QWidget *parent = 0);
    ~AntColonyTestDialog();
    int getStartQ();
    int getEndQ();
    int getIncrementQ();
    int getStartMods();
    int getEndMods();
    int getIncrementMods();
    int getStartEvaporation();
    int getEndEvaporation();
    int getIncrementEvaporation();
    int getStartInfluence();
    int getEndInfluence();
    int getIncrementInfluence();


private slots:
    void on_pushButtonAccept_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::AntColonyTestDialog *ui;
};

#endif // ANTCOLONYTESTDIALOG_H
