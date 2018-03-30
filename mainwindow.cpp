#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();
    series = new QLineSeries();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRead_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
    try{
        problem.setUpProblem(fileName);
    }catch(const std::invalid_argument ex){
        QMessageBox::information(this, "Error", "Wrong file formatting.");
    }
    population.setUpPopulation(ui->lineEditSeed->text().toInt(),
                               ui->lineEditPopulation->text().toInt(),
                               ui->lineEditGenerations->text().toInt(),
                               ui->lineEditElitism->text().toInt(),
                               ui->lineEditMutation->text().toInt(),
                               problem);
    population.calculateFitnesses(problem);
    ui->labelNodes->setText("Nodes: " + QString::number(problem.getTotal()) + " Connections: " + QString::number(problem.getConnections()));
    chart->axisY()->setRange(0,population.getBestIndividual().getFitness());
    updateForm();
}

void MainWindow::on_pushButtonSolve_clicked()
{
    solve();
}

void MainWindow::solve(){
    while(population.generateNewPopulation() == 1){
        population.calculateFitnesses(problem);
        updateForm();
    }
}

void MainWindow::updateForm(){
    Individual bestIndividual = population.getBestIndividual();
    series->append(population.getGeneration(), bestIndividual.getFitness());
    chart->axisX()->setRange(0,population.getGeneration());
    ui->labelDisconnected->setText("Disconnected: " + QString::number(bestIndividual.getDisconnected()));
    ui->labelRegenerators->setText("Regenerators: " + QString::number(bestIndividual.getRegenerators()));
    ui->labelFitness->setText("Fitness: " + QString::number(bestIndividual.getFitness()));
}
