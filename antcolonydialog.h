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

namespace Ui {
class AntColonyDialog;
}

class AntColonyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AntColonyDialog(QWidget *parent = 0);
    ~AntColonyDialog();
    void clearGraph();

private slots:
    void on_pushButtonRead_clicked();

private:
    Ui::AntColonyDialog *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    AntColonyAlgorithm algorithm;
    AntColonyThread* mainThread;
};

#endif // ANTCOLONYDIALOG_H