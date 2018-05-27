#ifndef GENETICDIALOG_H
#define GENETICDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "geneticalgorithm.h"
#include "geneticthread.h"
#include "geneticmultithread.h"
#include "genetictestdialog.h"
#include "genetictestmultithread.h"

namespace Ui {
class GeneticDialog;
}

class GeneticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneticDialog(QWidget *parent = 0);
    ~GeneticDialog();

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
    Ui::GeneticDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QVector<QLabel*> labels;
    GeneticThread* mainThread;
    QVector<GeneticMultiThread*> threads;
    QVector<GeneticTestMultiThread*> test;
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
};

#endif // GENETICDIALOG_H
