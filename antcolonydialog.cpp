#include "antcolonydialog.h"
#include "ui_AntColonyDialog.h"

AntColonyDialog::AntColonyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AntColonyDialog)
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

AntColonyDialog::~AntColonyDialog()
{
    delete ui;
}

void AntColonyDialog::on_pushButtonRead_clicked()
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
    algorithm.setUpAlgorithm(0, ui->lineEditGenerations->text().toInt(), ui->lineEditQProb->text().toDouble(),
                             ui->lineEditQ->text().toDouble(), ui->lineEditMods->text().toInt(),
                             &population, &problem, ui->lineEditEvaporation->text().toDouble(),
                             ui->lineEditInflunce->text().toDouble());
    population.calculateFitnesses(&problem);
    ui->labelNodes->setText("Nodes: " + QString::number(problem.getTotal()) + " Connections: " + QString::number(problem.getConnections()));
    chart->axisY()->setRange(0, population.getBestIndividual().getFitness());
    clearGraph();
}

void AntColonyDialog::clearGraph(){
    series->clear();
    series->append(algorithm.getGeneration(), population.getBestIndividual().getFitness());
    chart->axisX()->setRange(0, 1);
    ui->labelDisconnected->setText("Disconnected: " + QString::number(population.getBestIndividual().getDisconnected()));
    ui->labelRegenerators->setText("Regenerators: " + QString::number(population.getBestIndividual().getRegenerators()));
    ui->labelFitness->setText("Fitness: " + QString::number(population.getBestIndividual().getFitness()));
}

void AntColonyDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Solve"){
        if(problem.getTotal()==0){
            QMessageBox::information(this, "Error", "Read a file first.");
            return;
        }

        population.setUpPopulation(ui->lineEditSeed->text().toInt(),
                                   ui->lineEditPopulation->text().toInt(),
                                   &problem);
        algorithm.setUpAlgorithm(0, ui->lineEditGenerations->text().toInt(), ui->lineEditQProb->text().toDouble(),
                                 ui->lineEditQ->text().toDouble(), ui->lineEditMods->text().toInt(),
                                 &population, &problem, ui->lineEditEvaporation->text().toDouble(),
                                 ui->lineEditInflunce->text().toDouble());
        population.calculateFitnesses(&problem);
        clearGraph();
        mainThread = new AntColonyThread(&population, &problem, &algorithm);
        connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
        mainThread->start();
        disableForm();
    }else{
        mainThread->terminate();
        enableForm();
    }
}

void AntColonyDialog::onDataChanged(QString stuff)
{
    QList<QString> moreStuff = stuff.split(" ");
    int seconds = moreStuff[4].toInt()%60;
    QString strsec="";
    if(seconds < 10){
        strsec += "0";
    }
    strsec += QString::number(seconds);
    int minutes = (moreStuff[4].toInt()%3600-seconds)/60;
    QString strmin;
    if(minutes < 10){
        strmin += "0";
    }
    strmin += QString::number(minutes);
    series->append(moreStuff[3].toInt(), moreStuff[0].toInt());
    chart->axisX()->setRange(0, moreStuff[3].toInt());
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
    ui->labelElapsed->setText("Elapsed Time: " + strmin + ":" + strsec);
    if(moreStuff[5] == "1"){
        enableForm();
    }
}


void AntColonyDialog::disableForm(){
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditQProb->setDisabled(true);
    ui->lineEditQ->setDisabled(true);
    ui->lineEditMods->setDisabled(true);
    ui->lineEditEvaporation->setDisabled(true);
    ui->lineEditInflunce->setDisabled(true);
    ui->pushButtonRead->setDisabled(true);
    ui->pushButtonSolve->setText("Stop");
}

void AntColonyDialog::enableForm(){
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditQProb->setDisabled(false);
    ui->lineEditQ->setDisabled(false);
    ui->lineEditMods->setDisabled(false);
    ui->lineEditEvaporation->setDisabled(false);
    ui->lineEditInflunce->setDisabled(false);
    ui->pushButtonRead->setDisabled(false);
    ui->pushButtonSolve->setText("Solve");
}

