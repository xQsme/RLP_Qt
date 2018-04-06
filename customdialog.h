#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "customalgorithm.h"
#include "customthread.h"

namespace Ui {
class CustomDialog;
}

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = 0);
    ~CustomDialog();
    void clearGraph();
    void disableForm();
    void enableForm();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonSolve_clicked();

private:
    Ui::CustomDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    CustomAlgorithm algorithm;
    CustomThread* mainThread;

public slots:
    void onDataChanged(QString);
};

#endif // CUSTOMDIALOG_H
