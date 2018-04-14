#include "beecolonydialog.h"
#include "ui_beecolonydialog.h"

BeeColonyDialog::BeeColonyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BeeColonyDialog)
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

BeeColonyDialog::~BeeColonyDialog()
{
    delete ui;
}

void BeeColonyDialog::clearLayout(){
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0){
        if (child->widget())
            delete child->widget();
        if (child->layout())
            delete child->layout();
        delete child;
    }
}

void BeeColonyDialog::enableGraph()
{
    clearLayout();
    ui->labelNodes->setVisible(true);
    ui->gridLayout->addWidget(chartView, 0, 0);
}

void BeeColonyDialog::enableThreads(){
    clearLayout();
    labels.clear();
    ui->labelNodes->setVisible(false);
    for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++){
        if(i < ui->comboBoxThreads->currentText().toInt()/2 + 1){
            labels << new QLabel("Thread " + QString::number(i));
            ui->gridLayout->addWidget(labels[labels.length()-1], 0, i);
            labels << new QLabel("File");
            ui->gridLayout->addWidget(labels[labels.length()-1], 1, i);
        }else{
            labels << new QLabel("Thread " + QString::number(i));
            ui->gridLayout->addWidget(labels[labels.length()-1], 3, i-ui->comboBoxThreads->currentText().toInt()/2-1);
            labels << new QLabel("File");
            ui->gridLayout->addWidget(labels[labels.length()-1], 4, i-ui->comboBoxThreads->currentText().toInt()/2-1);
        }
    }
}

void BeeColonyDialog::on_pushButtonRead_clicked()
{
    if(ui->pushButtonRead->text() == "Solve")
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
        if(fileName != ""){
            enableGraph();
            mainThread = new BeeColonyThread(fileName, ui->lineEditSeed->text().toInt(),
                                          ui->lineEditPopulation->text().toInt(),
                                          ui->lineEditGenerations->text().toInt(),
                                          ui->lineEditSelectSize->text().toInt(),
                                          ui->lineEditBestSize->text().toInt(),
                                          ui->lineEditSelectValue->text().toInt(),
                                          ui->lineEditBestValue->text().toInt(),
                                          ui->lineEditChangeValue->text().toInt());
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

void BeeColonyDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
        if(dir.dirName() != ""){
            enableThreads();
            QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm_settings.csv");
            info.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream infoStream(&info);
            infoStream << "Seed: " << ui->lineEditSeed->text() << endl;
            infoStream << "Population: " <<  ui->lineEditPopulation->text() << endl;
            infoStream << "Generations: " <<  ui->lineEditGenerations->text() << endl;
            infoStream << "Select Size: " <<  ui->lineEditSelectSize->text() << endl;
            infoStream << "Best Size: " <<  ui->lineEditBestSize->text() << endl;
            infoStream << "Select Value: " <<  ui->lineEditSelectValue->text() << "%" << endl;
            infoStream << "Best Value: " <<  ui->lineEditBestValue->text() << "%" << endl;
            infoStream << "Change Value: " <<  ui->lineEditChangeValue->text() << endl;
            info.close();

            file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm.csv");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            stream.setDevice(&file);
            stream << "File;Generations;Time;Fitness;Regenerators;Disconnected" << endl;
            threads.clear();
            for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
            {
                threads << new BeeColonyMultiThread(dir, ui->lineEditSeed->text().toInt(),
                                                    ui->lineEditPopulation->text().toInt(),
                                                    ui->lineEditGenerations->text().toInt(),
                                                    ui->lineEditSelectSize->text().toInt(),
                                                    ui->lineEditBestSize->text().toInt(),
                                                    ui->lineEditSelectValue->text().toInt(),
                                                    ui->lineEditBestValue->text().toInt(),
                                                    ui->lineEditChangeValue->text().toInt(),
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

void BeeColonyDialog::singleProblem(QString stuff){
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

void BeeColonyDialog::onDataChanged(QString stuff)
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

void BeeColonyDialog::disableForm(int batch)
{
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditSelectSize->setDisabled(true);
    ui->lineEditBestSize->setDisabled(true);
    ui->lineEditSelectValue->setDisabled(true);
    ui->lineEditBestValue->setDisabled(true);
    ui->lineEditChangeValue->setDisabled(true);
    if(batch == 1){
        ui->pushButtonSolve->setText("Stop");
        ui->pushButtonRead->setDisabled(true);
    }else{
        ui->pushButtonRead->setText("Stop");
        ui->pushButtonSolve->setDisabled(true);
    }
}

void BeeColonyDialog::enableForm()
{
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditSelectSize->setDisabled(false);
    ui->lineEditBestSize->setDisabled(false);
    ui->lineEditSelectValue->setDisabled(false);
    ui->lineEditBestValue->setDisabled(false);
    ui->lineEditChangeValue->setDisabled(false);
    if(ui->pushButtonSolve->text() == "Stop"){
        ui->pushButtonSolve->setText("Batch Solve");
        ui->pushButtonRead->setDisabled(false);
    }else{
        ui->pushButtonRead->setText("Close");
        ui->pushButtonSolve->setDisabled(false);
    }

}

void BeeColonyDialog::newProblem(int thread, QString fileName, int percent)
{
    labels[thread*2+1]->setText(fileName);
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        ui->progressBar->setValue(100);
    }
    else
    {
        ui->progressBar->setValue(percent);
    }
}

void BeeColonyDialog::problemEnded(QString stuff, int ended)
{
    stream << stuff << endl;
    if(ended == 1){
        enableForm();
        file.close();
        ui->progressBar->setValue(100);
    }
}
