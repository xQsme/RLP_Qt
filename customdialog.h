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
    void disableForm();
    void enableForm();
    void solveSingle(QString fileName);
    void solveMultiple(QString fileName);
    Ui::CustomDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    CustomAlgorithm algorithm;
    CustomThread* mainThread;
    QDir dir;
    QFile file;
    QTextStream stream;
    int totalFiles;
    int count=0;
    QVector<CustomMultiThread*> threads;
    QVector<Population> populations;
    QVector<Problem> problems;
    QVector<CustomAlgorithm> algorithms;

public slots:
    void onDataChanged(QString);
    void threadEnded(QString, int count);
};

#endif // CUSTOMDIALOG_H
