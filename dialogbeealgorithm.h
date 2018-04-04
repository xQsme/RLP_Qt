#ifndef DIALOGBEEALGORITHM_H
#define DIALOGBEEALGORITHM_H

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
class DialogBeeAlgorithm;
}

class DialogBeeAlgorithm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBeeAlgorithm(QWidget *parent = 0);
    ~DialogBeeAlgorithm();

private:
    Ui::DialogBeeAlgorithm *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    MainThread* mainThread;
};

#endif // DIALOGBEEALGORITHM_H
