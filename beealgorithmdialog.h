#ifndef BEEALGORITHMDIALOG_H
#define BEEALGORITHMDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"
#include "beealgorithm.h"
#include "beealgorithmthread.h"

namespace Ui {
class BeeAlgorithmDialog;
}

class BeeAlgorithmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeeAlgorithmDialog(QWidget *parent = 0);
    ~BeeAlgorithmDialog();
     void clearGraph();

private slots:
    void on_pushButtonRead_clicked();

private:
    Ui::BeeAlgorithmDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    BeeAlgorithm algorithm;
    BeeAlgorithmThread* mainThread;
};

#endif // BEEALGORITHMDIALOG_H
