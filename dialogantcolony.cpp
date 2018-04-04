#include "dialogantcolony.h"
#include "ui_dialogantcolony.h"

DialogAntColony::DialogAntColony(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAntColony)
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

DialogAntColony::~DialogAntColony()
{
    delete ui;
}

void DialogAntColony::on_pushButtonRead_clicked()
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
                               &problem);
    algorithm.setUpAlgorithm(0, ui->lineEditElitism->text().toInt(),
                             ui->lineEditMutation->text().toInt(),
                             ui->lineEditGenerations->text().toInt());
    population.calculateFitnesses(&problem);
    ui->labelNodes->setText("Nodes: " + QString::number(problem.getTotal()) + " Connections: " + QString::number(problem.getConnections()));
    chart->axisY()->setRange(0, population.getBestIndividual().getFitness());
    clearGraph();
}
