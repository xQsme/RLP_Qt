#include "customdialog.h"
#include "ui_customdialog.h"

using namespace QtCharts;

CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDialog)
{
    ui->setupUi(this);
    ui->comboBoxThreads->addItem(tr("3"));
    ui->comboBoxThreads->addItem(tr("5"));

    chart = new QChart();
    series = new QLineSeries();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->labelNodes->setVisible(false);
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::clearLayout(){
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0){
        if (child->widget())
            delete child->widget();
        if (child->layout())
            delete child->layout();
        delete child;
    }
}

void CustomDialog::enableGraph()
{
    clearLayout();
    ui->labelNodes->setVisible(true);
    ui->labelDisconnected->setVisible(true);
    ui->labelRegenerators->setVisible(true);
    ui->labelFitness->setVisible(true);
    ui->gridLayout->addWidget(chartView, 0, 0);
}

void CustomDialog::enableThreads(){
    clearLayout();
    labels.clear();
    ui->labelNodes->setVisible(false);
    ui->labelDisconnected->setVisible(false);
    ui->labelRegenerators->setVisible(false);
    ui->labelFitness->setVisible(false);
    for(int i = 0; i <= 2; i++){
        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        ui->gridLayout->addWidget(line, i*3, 0, 1, ui->comboBoxThreads->currentText().toInt()+2);
    }
    for(int i = 0; i <= ui->comboBoxThreads->currentText().toInt()/2+1; i++){
        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        ui->gridLayout->addWidget(line, 0, i*2, 7, 1);
    }
    for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++){
        if(i <= ui->comboBoxThreads->currentText().toInt()/2){
            labels << new QLabel("Thread " + QString::number(i));
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 1, i*2+1);
            labels << new QLabel("File");
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 2, i*2+1);
        }else{
            labels << new QLabel("Thread " + QString::number(i));
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 4, (i-ui->comboBoxThreads->currentText().toInt()/2-1)*2+1);
            labels << new QLabel("File");
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 5, (i-ui->comboBoxThreads->currentText().toInt()/2-1)*2+1);
        }
    }
}

void CustomDialog::on_pushButtonRead_clicked()
{
    if(ui->pushButtonRead->text() == "Solve")
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
        if(fileName != ""){
            enableGraph();
            mainThread = new CustomThread(fileName, ui->lineEditSeed->text().toInt(),
                                          ui->lineEditPopulation->text().toInt(),
                                          ui->lineEditGenerations->text().toInt(),
                                          ui->lineEditElitism->text().toInt(),
                                          ui->lineEditMutation->text().toInt());
            connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
            connect(mainThread, SIGNAL(singleProblem(QString)), this, SLOT(singleProblem(QString)));
            mainThread->start();
            disableForm(0);
        }
        else
        {
            QMessageBox::information(this, "Error", "Please select a file.");
        }
    }
    else if(ui->pushButtonRead->text() == "Close")
    {
        close();
    }
    else
    {
        mainThread->terminate();
        enableForm();
    }

}

void CustomDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
        if(dir.dirName() != "."){
            ui->progressBar->setValue(0);
            enableThreads();
            QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm_settings.csv");
            info.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream infoStream(&info);
            infoStream << "Seed: " << ui->lineEditSeed->text() << endl;
            infoStream << "Population: " <<  ui->lineEditPopulation->text() << endl;
            infoStream << "Generations: " <<  ui->lineEditGenerations->text() << endl;
            infoStream << "Elitism: " <<  ui->lineEditElitism->text() << "%" << endl;
            infoStream << "Mutation: " <<  ui->lineEditMutation->text() << "%" << endl;
            info.close();

            file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm.csv");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            stream.setDevice(&file);
            stream << "File;Generations;Time;Fitness;Regenerators;Disconnected" << endl;
            threads.clear();
            for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
            {
                threads << new CustomMultiThread(dir, ui->lineEditSeed->text().toInt(),
                                                    ui->lineEditPopulation->text().toInt(),
                                                    ui->lineEditGenerations->text().toInt(),
                                                    ui->lineEditElitism->text().toInt(),
                                                    ui->lineEditMutation->text().toInt(),
                                                    i, ui->comboBoxThreads->currentText().toInt());
                connect(threads[i], SIGNAL(newProblem(int, QString, int)), this, SLOT(newProblem(int, QString, int)));
                connect(threads[i], SIGNAL(problemEnded(QString, int)), this, SLOT(problemEnded(QString, int)));
                threads[i]->start();
            }
            disableForm(1);
        }
        else
        {
            QMessageBox::information(this, "Error", "Please select a directory.");
        }
    }
    else{
        for(int i = 0; i < threads.length(); i++)
        {
            threads[i]->terminate();
        }
        enableForm();
        file.close();
    }
}

void CustomDialog::singleProblem(QString stuff){
    QList<QString> moreStuff = stuff.split(" ");
    ui->labelNodes->setText("Nodes: " + moreStuff[3]  + " Connections: " + moreStuff[4]);
    series->clear();
    series->append(0, moreStuff[0].toInt());
    int range = moreStuff[0].toInt();
    while(range % 1000 != 0){
        range+=100;
    }
    chart->axisY()->setRange(0, range);
    chart->axisX()->setRange(0, 1);
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
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
    ui->progressBar->setValue(moreStuff[6].toInt());
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
        ui->pushButtonRead->setText("Close");
        ui->pushButtonSolve->setDisabled(false);
    }
}

void CustomDialog::newProblem(int thread, QString fileName, int percent, int time)
{
    labels[thread*2+1]->setText(fileName);
    if(percent > ui->progressBar->value())
    {
        ui->progressBar->setValue(percent);
    }
    int seconds = time%60;
    QString strsec="";
    if(seconds < 10){
        strsec += "0";
    }
    strsec += QString::number(seconds);
    int minutes = (time%3600-seconds)/60;
    QString strmin;
    if(minutes < 10){
        strmin += "0";
    }
    strmin += QString::number(minutes);
    ui->labelElapsed->setText("Elapsed Time: " + strmin + ":" + strsec);
}

void CustomDialog::problemEnded(QString stuff, int ended)
{
    stream << stuff << endl;
    if(ended == 1){
        enableForm();
        ui->progressBar->setValue(100);
    }
}
