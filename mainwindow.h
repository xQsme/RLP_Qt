#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "antcolonydialog.h"
#include "geneticdialog.h"
#include "beecolonydialog.h"
#include "customdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void on_pushButtonCustom_clicked();

    void on_pushButtonAntColony_clicked();

    void on_pushButtonBeeColony_clicked();

    void on_pushButtonGeneticAlgorithm_clicked();

private:
    Ui::MainWindow *ui;

public slots:
};

#endif // MAINWINDOW_H
