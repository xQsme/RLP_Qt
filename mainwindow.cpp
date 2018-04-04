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
    DialogCustom dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonAntColony_clicked()
{
    DialogAntColony dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonBeeAlgorithm_clicked()
{
    DialogBeeAlgorithm dialog;
    dialog.exec();
}

void MainWindow::on_pushButtonBeeColony_clicked()
{
    DialogBeeColony dialog;
    dialog.exec();
}
