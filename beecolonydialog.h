#ifndef BEECOLONYDIALOG_H
#define BEECOLONYDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "beecolonyalgorithm.h"
#include "beecolonythread.h"
#include "beecolonymultithread.h"

namespace Ui {
class BeeColonyDialog;
}

class BeeColonyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeeColonyDialog(QWidget *parent = 0);
    ~BeeColonyDialog();

private slots:
    void on_pushButtonRead_clicked();
    void on_pushButtonSolve_clicked();
    void update();

private:
    void clearLayout();
    void disableForm(int batch);
    void enableForm();
    void enableGraph();
    void enableThreads();
    Ui::BeeColonyDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    QVector<QLabel*> labels;
    BeeColonyThread* mainThread;
    QVector<BeeColonyMultiThread*> threads;
    QTextStream stream;
    QFile file;
    QTimer timer;
    QElapsedTimer elapsed;

public slots:
    void onDataChanged(QString stuff);
    void singleProblem(QString stuff);
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // BEECOLONYDIALOG_H
