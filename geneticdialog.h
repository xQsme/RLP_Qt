#ifndef GENETICDIALOG_H
#define GENETICDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "geneticalgorithm.h"
#include "geneticthread.h"

namespace Ui {
class GeneticDialog;
}

class GeneticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneticDialog(QWidget *parent = 0);
    ~GeneticDialog();
     void clearGraph();

private slots:
    void on_pushButtonRead_clicked();

private:
    Ui::GeneticDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    GeneticThread* mainThread;
};

#endif // GENETICDIALOG_H
