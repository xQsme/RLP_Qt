#ifndef DIALOGANTCOLONY_H
#define DIALOGANTCOLONY_H

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
class DialogAntColony;
}

class DialogAntColony : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAntColony(QWidget *parent = 0);
    ~DialogAntColony();

private:
    Ui::DialogAntColony *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    MainThread* mainThread;
};

#endif // DIALOGANTCOLONY_H
