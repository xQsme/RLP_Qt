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
        solveSingle(fileName);
        disableForm();
    }
    else{
        mainThread->terminate();
        enableForm();
    }

}

void CustomDialog::on_pushButtonSolve_clicked()
{
    dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
    if(dir.dirName() != ""){
        QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm_settings.csv");
        info.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream infoStream(&info);
        infoStream << "Seed: " << ui->lineEditSeed->text() << endl;
        infoStream << "Population: " << ui->lineEditPopulation->text() << endl;
        infoStream << "Generations: " << ui->lineEditGenerations->text() << endl;
        infoStream << "Elitism: " << ui->lineEditElitism->text() << "%" << endl;
        infoStream << "Mutation: " << ui->lineEditMutation->text() << "%" << endl;

        file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm.csv");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        stream.setDevice(&file);
        stream << "Generations;Time;Fitness;Regenerators;Disconnected" << endl;
        totalFiles = dir.entryInfoList().length();
        foreach(QFileInfo problem, dir.entryInfoList())
        {
            if(!dir.absolutePath().contains(problem.absoluteFilePath()))
            {
                solveMultiple(problem.absoluteFilePath());
                if(++count == ui->lineEditThreads->text().toInt()){
                    break;
                }
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Error", "Please select a directory.");
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

void CustomDialog::threadEnded(QString stuff, int count)
{
    stream << stuff << endl;
    //stream->operator <<(endl);
    //threads[count]= NULL;
    //problems[count] = Problem();
    //populations[count] = Population();
    //algorithms[count] = CustomAlgorithm();
    if(++count < totalFiles-1){
        solveMultiple(dir.entryInfoList()[count+3].absoluteFilePath());
    }
}

void CustomDialog::disableForm()
{
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditElitism->setDisabled(true);
    ui->lineEditMutation->setDisabled(true);
    ui->pushButtonRead->setText("Stop");
    ui->pushButtonSolve->setDisabled(true);
}

void CustomDialog::enableForm()
{
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditElitism->setDisabled(false);
    ui->lineEditMutation->setDisabled(false);
    ui->pushButtonRead->setText("Solve");
    ui->pushButtonSolve->setDisabled(false);
}

void CustomDialog::solveSingle(QString fileName)
{
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
    mainThread = new CustomThread(&population, &problem, &algorithm);
    connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
    mainThread->start();
}

void CustomDialog::solveMultiple(QString fileName)
{
    problems << Problem();
    try{
        problems[count].setUpProblem(fileName);
    }catch(const std::invalid_argument ex){
        QMessageBox::information(this, "Error", "Wrong file formatting.");
    }
    populations << Population();
    populations[count].setUpPopulation(ui->lineEditSeed->text().toInt(),
                               ui->lineEditPopulation->text().toInt(),
                               &problems[count]);
    algorithms << CustomAlgorithm();
    algorithms[count].setUpAlgorithm(0, ui->lineEditElitism->text().toInt(),
                             ui->lineEditMutation->text().toInt(),
                             ui->lineEditGenerations->text().toInt());
    //populations[count].calculateFitnesses(&problems[count]);
    threads << new CustomMultiThread(&populations[count], &problems[count], &algorithms[count], count);
    connect(threads[count], SIGNAL(threadEnded(QString, int)), this, SLOT(threadEnded(QString, int)));
    threads[count]->start();
}
