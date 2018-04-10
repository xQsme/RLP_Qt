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

private slots:
    void on_pushButtonRead_clicked();
    void on_pushButtonSolve_clicked();

private:
    void clearGraph();
    void disableForm();
    void enableForm();
    Ui::BeeColonyDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    BeeColonyAlgorithm algorithm;
    BeeColonyThread* mainThread;

public slots:
    void onDataChanged(QString);
};

#endif // BEECOLONYDIALOG_H
