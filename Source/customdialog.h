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
#include "customtestdialog.h"
#include "customtestmultithread.h"

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
    void update();

    void on_pushButtonSolve_2_clicked();

private:
    void clearLayout();
    void disableForm(int batch);
    void enableForm();
    void enableGraph();
    void enableThreads();
    Ui::CustomDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QVector<QLabel*> labels;
    CustomThread* mainThread;
    QVector<CustomMultiThread*> threads;
    QVector<CustomTestMultiThread*> test;
    QTextStream stream;
    QFile file;
    QElapsedTimer elapsed;
    QTimer timer;
    int previous=-1;
    int done=0;

public slots:
    void onDataChanged(QString stuff);
    void singleProblem(QString stuff);
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
    void wrongFile();
};

#endif // CUSTOMDIALOG_H
