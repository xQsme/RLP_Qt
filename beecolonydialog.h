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

namespace Ui {
class BeeColonyDialog;
}

class BeeColonyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeeColonyDialog(QWidget *parent = 0);
    ~BeeColonyDialog();
    void clearGraph();

private slots:
    void on_pushButtonRead_clicked();

private:
    Ui::BeeColonyDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    BeeColonyAlgorithm algorithm;
    BeeColonyThread* mainThread;
};

#endif // BEECOLONYDIALOG_H
