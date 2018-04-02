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
                               &problem);
    population.calculateFitnesses(&problem);
    ui->labelNodes->setText("Nodes: " + QString::number(problem.getTotal()) + " Connections: " + QString::number(problem.getConnections()));
    chart->axisY()->setRange(0, population.getBestIndividual().getFitness());
    clearGraph();
}

void MainWindow::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Solve"){
        if(problem.getTotal()==0){
            QMessageBox::information(this, "Error", "Read a file first.");
            return;
        }
        if(population.getGeneration() >= population.getGenerations() ||
                population.getGenerations() != ui->lineEditGenerations->text().toInt() ||
                population.getPopulationSize() != ui->lineEditPopulation->text().toInt() ||
                population.getElitism() != ui->lineEditElitism->text().toInt() ||
                population.getMutation() != ui->lineEditMutation->text().toInt() ||
                population.getSeed() != ui->lineEditSeed->text().toInt()){
            if(population.getSeed() != ui->lineEditSeed->text().toInt() ||
                    population.getPopulationSize() != ui->lineEditPopulation->text().toInt() ||
                    population.getGeneration() >= population.getGenerations()){
                population.setUpPopulation(ui->lineEditSeed->text().toInt(),
                                           ui->lineEditPopulation->text().toInt(),
                                           ui->lineEditGenerations->text().toInt(),
                                           ui->lineEditElitism->text().toInt(),
                                           ui->lineEditMutation->text().toInt(),
                                           &problem);
                population.calculateFitnesses(&problem);
                clearGraph();
            }else{
                population.setUpPopulation(ui->lineEditGenerations->text().toInt(),
                                           ui->lineEditElitism->text().toInt(),
                                           ui->lineEditMutation->text().toInt());
            }
        }
        mainThread = new MainThread(&population, &problem/*, ui->lineEditThreads->text().toInt()*/);
        connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
        mainThread->start();
        disableForm();
    }else{
        mainThread->terminate();
        enableForm();
    }
}

void MainWindow::clearGraph(){
    series->clear();
    series->append(population.getGeneration(), population.getBestIndividual().getFitness());
    chart->axisX()->setRange(0, 1);
}

void MainWindow::onDataChanged(QString stuff)
{
    QList<QString> moreStuff = stuff.split(" ");
    series->append(moreStuff[3].toInt(), moreStuff[0].toInt());
    chart->axisX()->setRange(0, moreStuff[3].toInt());
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
    if(moreStuff[4] == "1"){
        enableForm();
    }
}

void MainWindow::disableForm(){
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditElitism->setDisabled(true);
    ui->lineEditMutation->setDisabled(true);
    ui->pushButtonRead->setDisabled(true);
    ui->pushButtonSolve->setText("Stop");
}

void MainWindow::enableForm(){
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditElitism->setDisabled(false);
    ui->lineEditMutation->setDisabled(false);
    ui->pushButtonRead->setDisabled(false);
    ui->pushButtonSolve->setText("Solve");
}
