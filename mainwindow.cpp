#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCustom_clicked()
{
    CustomDialog dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonAntColony_clicked()
{
    AntColonyDialog dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonBeeAlgorithm_clicked()
{
    BeeAlgorithmDialog dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonBeeColony_clicked()
{
    BeeColonyDialog dialog;
    dialog.exec();
}
