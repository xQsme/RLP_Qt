#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QFileDialog>
#include <QMessageBox>
#include "problem.h"
#include "individual.h"
#include "population.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateForm();
    void solve();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonSolve_clicked();

private:
    Ui::MainWindow *ui;
    QChart *chart;
    QLineSeries *series;
    QChartView *chartView;
    Population population;
};

#endif // MAINWINDOW_H
