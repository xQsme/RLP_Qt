#ifndef DIALOGBEECOLONY_H
#define DIALOGBEECOLONY_H

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
class DialogBeeColony;
}

class DialogBeeColony : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBeeColony(QWidget *parent = 0);
    ~DialogBeeColony();

private slots:
    void on_pushButtonRead_clicked();

private:
    Ui::DialogBeeColony *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    MainThread* mainThread;
};

#endif // DIALOGBEECOLONY_H
