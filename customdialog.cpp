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

void CustomDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Solve"){
        if(problem.getTotal()==0){
            QMessageBox::information(this, "Error", "Read a file first.");
            return;
        }
        if(algorithm.getGeneration() >= algorithm.getGenerations() ||
                algorithm.getGenerations() != ui->lineEditGenerations->text().toInt() ||
                population.getPopulationSize() != ui->lineEditPopulation->text().toInt() ||
                algorithm.getElitism() - ui->lineEditElitism->text().toInt() * 0.01 >= 0.001 ||
                algorithm.getElitism() - ui->lineEditElitism->text().toInt() * 0.01 <= -0.001 ||
                algorithm.getMutation() - ui->lineEditMutation->text().toInt() * 0.01 >= 0.001 ||
                algorithm.getMutation() - ui->lineEditMutation->text().toInt() * 0.01 <= -0.001 ||
                population.getSeed() != ui->lineEditSeed->text().toInt()){ //Se mudou alguma coisa ou chegou ao fim
            if(population.getSeed() != ui->lineEditSeed->text().toInt() ||
                    population.getPopulationSize() != ui->lineEditPopulation->text().toInt()){ //Se a população mudou
                population.setUpPopulation(ui->lineEditSeed->text().toInt(),
                                           ui->lineEditPopulation->text().toInt(),
                                           &problem);
                algorithm.setUpAlgorithm(0, ui->lineEditElitism->text().toInt(),
                                         ui->lineEditMutation->text().toInt(),
                                         ui->lineEditGenerations->text().toInt());
                population.calculateFitnesses(&problem);
                clearGraph();
            }else if(ui->lineEditGenerations->text().toInt() > algorithm.getGeneration() &&
                     algorithm.getElitism() - ui->lineEditElitism->text().toInt() * 0.01 <= 0.001 &&
                     algorithm.getElitism() - ui->lineEditElitism->text().toInt() * 0.01 >= -0.001 &&
                     algorithm.getMutation() - ui->lineEditMutation->text().toInt() * 0.01 <= 0.001 &&
                     algorithm.getMutation() - ui->lineEditMutation->text().toInt() * 0.01 >= -0.001){ //Se apenas as gerações mudaram
                algorithm.setUpAlgorithm(1, ui->lineEditElitism->text().toInt(),
                                         ui->lineEditMutation->text().toInt(),
                                         ui->lineEditGenerations->text().toInt());
            }else{ //Mudou algo que não as gerações
                population.setUpPopulation(ui->lineEditSeed->text().toInt(),
                                           ui->lineEditPopulation->text().toInt(),
                                           &problem);
                population.calculateFitnesses(&problem);
                algorithm.setUpAlgorithm(0, ui->lineEditElitism->text().toInt(),
                                         ui->lineEditMutation->text().toInt(),
                                         ui->lineEditGenerations->text().toInt());
                clearGraph();
            }
        }
        mainThread = new CustomThread(&population, &problem, &algorithm/*, ui->lineEditThreads->text().toInt()*/);
        connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
        mainThread->start();
        disableForm();
    }else{
        mainThread->terminate();
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
}

void CustomDialog::disableForm(){
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditElitism->setDisabled(true);
    ui->lineEditMutation->setDisabled(true);
    ui->pushButtonRead->setDisabled(true);
    ui->pushButtonSolve->setText("Stop");
}

void CustomDialog::enableForm(){
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditElitism->setDisabled(false);
    ui->lineEditMutation->setDisabled(false);
    ui->pushButtonRead->setDisabled(false);
    ui->pushButtonSolve->setText("Solve");
}
