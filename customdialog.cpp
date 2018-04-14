#include "customdialog.h"
#include "ui_customdialog.h"

using namespace QtCharts;

CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDialog)
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

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::on_pushButtonRead_clicked()
{
    if(ui->pushButtonRead->text() == "Solve")
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
        if(fileName != ""){
            solveSingle(fileName);
            disableForm(0);
        }
        else
        {
            QMessageBox::information(this, "Error", "Please select a file.");
        }
    }
    else{
        mainThread->terminate();
        enableForm();
    }

}

void CustomDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
        if(dir.dirName() != ""){
            multiThread = new CustomMultiThread(dir, ui->lineEditSeed->text().toInt(),
                                                ui->lineEditPopulation->text().toInt(),
                                                ui->lineEditGenerations->text().toInt(),
                                                ui->lineEditElitism->text().toInt(),
                                                ui->lineEditMutation->text().toInt());
            connect(multiThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
            connect(multiThread, SIGNAL(newProblem(QString)), this, SLOT(newProblem(QString)));
            multiThread->start();
            disableForm(1);
        }
        else
        {
            QMessageBox::information(this, "Error", "Please select a directory.");
        }
    }
    else{
        multiThread->terminate();
        enableForm();
    }
}

void CustomDialog::clearGraph(){
    series->clear();
    series->append(algorithm.getGeneration(), population.getBestIndividual().getFitness());
    chart->axisX()->setRange(0, 1);
    ui->labelDisconnected->setText("Disconnected: " + QString::number(population.getBestIndividual().getDisconnected()));
    ui->labelRegenerators->setText("Regenerators: " + QString::number(population.getBestIndividual().getRegenerators()));
    ui->labelFitness->setText("Fitness: " + QString::number(population.getBestIndividual().getFitness()));
    ui->labelElapsed->setText("Elapsed Time: 00:00");
}

void CustomDialog::onDataChanged(QString stuff)
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
    ui->progressBar->setValue(moreStuff[6].toFloat()*100);
}

void CustomDialog::disableForm(int batch)
{
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditElitism->setDisabled(true);
    ui->lineEditMutation->setDisabled(true);
    if(batch == 1){
        ui->pushButtonSolve->setText("Stop");
        ui->pushButtonRead->setDisabled(true);
    }else{
        ui->pushButtonRead->setText("Stop");
        ui->pushButtonSolve->setDisabled(true);
    }
}

void CustomDialog::enableForm()
{
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditElitism->setDisabled(false);
    ui->lineEditMutation->setDisabled(false);
    if(ui->pushButtonSolve->text() == "Stop"){
        ui->pushButtonSolve->setText("Batch Solve");
        ui->pushButtonRead->setDisabled(false);
    }else{
        ui->pushButtonRead->setText("Solve");
        ui->pushButtonSolve->setDisabled(false);
    }

}

void CustomDialog::solveSingle(QString fileName)
{
    try{
        problem.setUpProblem(fileName);
    }catch(const std::invalid_argument ex){
        QMessageBox::information(this, "Error", "Wrong file formatting.");
        return;
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
    mainThread = new CustomThread(&population, &problem, &algorithm);
    connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
    mainThread->start();
}

void CustomDialog::newProblem(QString stuff)
{
    QList<QString> moreStuff = stuff.split(" ");
    ui->labelNodes->setText("Nodes: " + moreStuff[0] + " Connections: " + moreStuff[1]);
    series->clear();
    series->append(0, moreStuff[2].toInt());
    chart->axisX()->setRange(0, 1);
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[3]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[4]);
    ui->labelFitness->setText("Fitness: " + moreStuff[2]);
    ui->labelElapsed->setText("Elapsed Time: 00:00");
}
