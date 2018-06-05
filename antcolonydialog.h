#ifndef ANTCOLONYDIALOG_H
#define ANTCOLONYDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "antcolonyalgorithm.h"
#include "antcolonythread.h"
#include "antcolonymultithread.h"
#include "antcolonytestdialog.h"
#include "antcolonytestmultithread.h"

namespace Ui {
class AntColonyDialog;
}

class AntColonyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AntColonyDialog(QWidget *parent = 0);
    ~AntColonyDialog();

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

    Ui::AntColonyDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QVector<QLabel*> labels;
    AntColonyThread* mainThread;
    QVector<AntColonyMultiThread*> threads;
    QVector<AntColonyTestMultiThread*> test;
    QTextStream stream;
    QFile file;
    QTimer timer;
    QElapsedTimer elapsed;
    int previous=-1;
    int done=0;

public slots:
    void onDataChanged(QString stuff);
    void singleProblem(QString stuff);
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // ANTCOLONYDIALOG_H
