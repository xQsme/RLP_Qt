#ifndef DIALOGCUSTOM_H
#define DIALOGCUSTOM_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "geneticalgorithm.h"
#include "mainthread.h"

namespace Ui {
class DialogCustom;
}

class DialogCustom : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCustom(QWidget *parent = 0);
    ~DialogCustom();
    void clearGraph();
    void disableForm();
    void enableForm();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonSolve_clicked();

private:
    Ui::DialogCustom *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    MainThread* mainThread;

public slots:
    void onDataChanged(QString);
};

#endif // DIALOGCUSTOM_H
