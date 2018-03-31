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
    chart->axisY()->setRange(0, population.getBestIndividual().getFitness());
    updateForm();
}

void MainWindow::on_pushButtonSolve_clicked()
{
    mainThread = new MainThread(population, problem);
    connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
    mainThread->start();
}

void MainWindow::solve(){

}

void MainWindow::updateForm(){

}

void MainWindow::onDataChanged(QString stuff)
{
    QList<QString> moreStuff = stuff.split(" ");
    series->append(moreStuff[3].toInt(), moreStuff[0].toInt());
    chart->axisX()->setRange(0, moreStuff[3].toInt());
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
}
