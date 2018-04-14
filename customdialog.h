#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "customalgorithm.h"
#include "customthread.h"
#include "custommultithread.h"

namespace Ui {
class CustomDialog;
}

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = 0);
    ~CustomDialog();

private slots:
    void on_pushButtonRead_clicked();
    void on_pushButtonSolve_clicked();

private:
    void clearGraph();
    void disableForm(int batch);
    void enableForm();
    void solveSingle(QString fileName);
    void solveMultiple(QString fileName, QString name);
    Ui::CustomDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    CustomAlgorithm algorithm;
    CustomThread* mainThread;
    CustomMultiThread* multiThread;

public slots:
    void onDataChanged(QString);
    void newProblem(QString);
};

#endif // CUSTOMDIALOG_H
