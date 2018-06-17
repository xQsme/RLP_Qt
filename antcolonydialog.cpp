#include "antcolonydialog.h"
#include "ui_antcolonydialog.h"

AntColonyDialog::AntColonyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AntColonyDialog)
{
    ui->setupUi(this);

    for(int i = QThread::idealThreadCount(); i > 0 ; i--){
        ui->comboBoxThreads->addItem(QString::number(i));
    }

    for(int i = 2; i < 100; i+=20)
    {
        ui->comboBoxSeeds->addItem(QString::number(i) + "-" + QString::number(i+18));
    }

    ui->comboBoxThreads->setCurrentIndex(1);

    chart = new QChart();
    series = new QLineSeries();

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->labelNodes->setVisible(false);


}

AntColonyDialog::~AntColonyDialog()
{
    delete ui;
}

void AntColonyDialog::clearLayout(){
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0){
        if (child->widget())
            delete child->widget();
        if (child->layout())
            delete child->layout();
        delete child;
    }
}

void AntColonyDialog::enableGraph()
{
    if(previous != 0)
    {
        clearLayout();
        ui->labelNodes->setVisible(true);
        ui->labelDisconnected->setVisible(true);
        ui->labelRegenerators->setVisible(true);
        ui->labelFitness->setVisible(true);
        ui->gridLayout->addWidget(chartView, 0, 0);
        previous=0;
    }
}

void AntColonyDialog::enableThreads(){
    if(previous == 0)
    {
        done = 1;
    }
    previous=1;
    clearLayout();
    labels.clear();
    ui->labelNodes->setVisible(false);
    ui->labelDisconnected->setVisible(false);
    ui->labelRegenerators->setVisible(false);
    ui->labelFitness->setVisible(false);
    for(int i = 0; i < 3; i++)
    {
        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        ui->gridLayout->addWidget(line, i*3, 0, 1, (ui->comboBoxThreads->currentText().toInt()+1)/2*2+1);
    }
    for(int i = 0; i < (ui->comboBoxThreads->currentText().toInt()+1)/2+1; i++)
    {
        QFrame* line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        ui->gridLayout->addWidget(line, 0, i*2, 7, 1);
    }
    for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++){
        if(i < (ui->comboBoxThreads->currentText().toInt()+1)/2)
        {
            labels << new QLabel("Thread " + QString::number(i));
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 1, i*2+1);
            labels << new QLabel("File");
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 2, i*2+1);
        }
        else
        {
            labels << new QLabel("Thread " + QString::number(i));
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 4, (i-(ui->comboBoxThreads->currentText().toInt()+1)/2)*2+1);
            labels << new QLabel("File");
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 5, (i-(ui->comboBoxThreads->currentText().toInt()+1)/2)*2+1);
        }
    }
    ui->labelElapsed->setText("Elapsed Time: 00:00");
}

void AntColonyDialog::on_pushButtonRead_clicked()
{
    if(ui->pushButtonRead->text() == "Solve")
    {
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
        if(fileName != ""){
            enableGraph();
            elapsed.start();
            connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
            timer.start(1000);
            mainThread = new AntColonyThread(fileName, ui->lineEditSeed->text().toInt(),
                                          ui->lineEditPopulation->text().toInt(),
                                          ui->lineEditGenerations->text().toInt(),
                                          ui->lineEditQProb->text().toInt(),
                                          ui->lineEditQ->text().toInt(),
                                          ui->lineEditMods->text().toInt(),
                                          ui->lineEditEvaporation->text().toInt(),
                                          ui->lineEditInflunce->text().toInt());
            connect(mainThread, SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));
            connect(mainThread, SIGNAL(singleProblem(QString)), this, SLOT(singleProblem(QString)));
            mainThread->start();
            disableForm(0);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Please select a file.");
            msgBox.addButton("Whatever", QMessageBox::AcceptRole);
            msgBox.exec();
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
        timer.stop();
    }

}

void AntColonyDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
        if(dir.dirName() != "."){
            ui->progressBar->setValue(0);
            enableThreads();
            QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_ant_colony_settings_" + ui->comboBoxSeeds->currentText() + ".txt");
            info.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream infoStream(&info);
            infoStream << "Population: " <<  ui->lineEditPopulation->text() << endl;
            infoStream << "Generations: " <<  ui->lineEditGenerations->text() << endl;
            infoStream << "Q probability: " <<  ui->lineEditQProb->text() << "%" << endl;
            infoStream << "Q: " <<  ui->lineEditQ->text() << endl;
            infoStream << "Modifications: " <<  ui->lineEditMods->text() << endl;
            infoStream << "Evaporation: " <<  ui->lineEditEvaporation->text() << "%" << endl;
            infoStream << "Influence: " <<  ui->lineEditInflunce->text() << "%" << endl;
            info.close();

            file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_ant_colony_" + ui->comboBoxSeeds->currentText() + ".csv");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            stream.setDevice(&file);
            stream << "Size;Problem;Instance;Seed;Generations;Time;Fitness;Regenerators;Disconnected" << endl;
            threads.clear();
            elapsed.start();
            connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
            timer.start(1000);
            for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
            {
                threads << new AntColonyMultiThread(dir.absolutePath(), ui->comboBoxSeeds->currentText().split("-")[0].toInt(),
                                                    ui->lineEditPopulation->text().toInt(),
                                                    ui->lineEditGenerations->text().toInt(),
                                                    ui->lineEditQProb->text().toInt(),
                                                    ui->lineEditQ->text().toInt(),
                                                    ui->lineEditMods->text().toInt(),
                                                    ui->lineEditEvaporation->text().toInt(),
                                                    ui->lineEditInflunce->text().toInt(),
                                                    i, ui->comboBoxThreads->currentText().toInt());
                connect(threads[i], SIGNAL(newProblem(int, QString, int)), this, SLOT(newProblem(int, QString, int)));
                connect(threads[i], SIGNAL(problemEnded(QString, int)), this, SLOT(problemEnded(QString, int)));
                threads[i]->start();
            }
            disableForm(1);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Please select a directory.");
            msgBox.addButton("Whatever", QMessageBox::AcceptRole);
            msgBox.exec();
        }
    }
    else{
        for(int i = 0; i < threads.length(); i++)
        {
            threads[i]->terminate();
        }
        enableForm();
        file.close();
        timer.stop();
    }
}

void AntColonyDialog::on_pushButtonSolve_2_clicked()
{
    if(ui->pushButtonSolve_2->text() == "Test")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets/test");
        if(dir.dirName() != ".")
        {
            AntColonyTestDialog dialog;
            dialog.setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
            if(dialog.exec() == QDialog::Accepted){
                ui->progressBar->setValue(0);
                enableThreads();
                QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_ant_colony_algorithm_settings.txt");
                info.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream infoStream(&info);
                infoStream << "Population: " <<  ui->lineEditPopulation->text() << endl;
                infoStream << "Generations: " <<  ui->lineEditGenerations->text() << endl;
                infoStream << "Q probability: " <<  ui->lineEditQProb->text() << "%" << endl;
                infoStream << "Q: " <<  dialog.getStartQ() << " to " << dialog.getEndQ() << " by "
                           << dialog.getIncrementQ() << endl;
                infoStream << "Modifications: " <<  dialog.getStartMods() << " to " << dialog.getEndMods() << " by "
                           << dialog.getIncrementMods() << endl;
                infoStream << "Evaporation: " <<  dialog.getStartEvaporation() << "% to " << dialog.getEndEvaporation() << "% by "
                           << dialog.getIncrementEvaporation() << "%" << endl;
                infoStream << "Influence: " <<  dialog.getStartInfluence() << "% to " << dialog.getEndInfluence() << "% by "
                           << dialog.getIncrementInfluence() << "%" << endl;
                info.close();

                file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_ant_colony_algorithm.csv");
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                stream.setDevice(&file);
                stream << "sep=;" << endl;
                stream << "Q;Modifications;Evaporation;Influence;Generations;Time;Regenerators;Disconnected" << endl;
                threads.clear();
                elapsed.start();
                connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
                timer.start(1000);
                for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
                {
                    test << new AntColonyTestMultiThread(dir.absolutePath(), ui->lineEditSeed->text().toInt(),
                                                        ui->lineEditPopulation->text().toInt(),
                                                        ui->lineEditGenerations->text().toInt(),
                                                        ui->lineEditQProb->text().toInt(),
                                                        dialog.getStartQ(),
                                                        dialog.getEndQ(),
                                                        dialog.getIncrementQ(),
                                                        dialog.getStartMods(),
                                                        dialog.getEndMods(),
                                                        dialog.getIncrementMods(),
                                                        dialog.getStartEvaporation(),
                                                        dialog.getEndEvaporation(),
                                                        dialog.getIncrementEvaporation(),
                                                        dialog.getStartInfluence(),
                                                        dialog.getEndInfluence(),
                                                        dialog.getIncrementInfluence(),
                                                        i, ui->comboBoxThreads->currentText().toInt());
                    connect(test[i], SIGNAL(newProblem(int, QString, int)), this, SLOT(newProblem(int, QString, int)));
                    connect(test[i], SIGNAL(problemEnded(QString, int)), this, SLOT(problemEnded(QString, int)));
                    test[i]->start();
                }
                disableForm(2);
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Please select a directory.");
            msgBox.addButton("Whatever", QMessageBox::AcceptRole);
            msgBox.exec();
        }
    }
    else
    {
        for(int i = 0; i < test.length(); i++)
        {
            test[i]->terminate();
        }
        enableForm();
        file.close();
        timer.stop();
    }
}


void AntColonyDialog::singleProblem(QString stuff){
    QList<QString> moreStuff = stuff.split(" ");
    ui->labelNodes->setText("Nodes: " + moreStuff[3]  + " Connections: " + moreStuff[4]);
    series->clear();
    series->append(0, moreStuff[0].toInt());
    int range = moreStuff[0].toInt();
    while(range % 1000 != 0)
    {
        range+=100;
    }
    chart->axisY()->setRange(0, range);
    chart->axisX()->setRange(0, 1);
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
    ui->labelElapsed->setText("Elapsed Time: 00:00");
}

void AntColonyDialog::onDataChanged(QString stuff)
{
    QList<QString> moreStuff = stuff.split(" ");
    series->append(moreStuff[3].toInt(), moreStuff[0].toInt());
    chart->axisX()->setRange(0, moreStuff[3].toInt());
    ui->labelDisconnected->setText("Disconnected: " + moreStuff[1]);
    ui->labelRegenerators->setText("Regenerators: " + moreStuff[2]);
    ui->labelFitness->setText("Fitness: " + moreStuff[0]);
    if(moreStuff[4] == "1")
    {
        enableForm();
        timer.stop();
    }
    ui->progressBar->setValue(moreStuff[5].toInt());
}

void AntColonyDialog::disableForm(int batch)
{
    ui->lineEditSeed->setDisabled(true);
    ui->lineEditPopulation->setDisabled(true);
    ui->lineEditGenerations->setDisabled(true);
    ui->lineEditQProb->setDisabled(true);
    ui->lineEditQ->setDisabled(true);
    ui->lineEditMods->setDisabled(true);
    ui->lineEditEvaporation->setDisabled(true);
    ui->lineEditInflunce->setDisabled(true);
    ui->comboBoxThreads->setDisabled(true);
    ui->comboBoxSeeds->setDisabled(true);
    switch(batch){
    case 0:
        ui->pushButtonRead->setText("Stop");
        ui->pushButtonSolve->setDisabled(true);
        ui->pushButtonSolve_2->setDisabled(true);
        break;
    case 1:
        ui->pushButtonSolve->setText("Stop");
        ui->pushButtonRead->setDisabled(true);
        ui->pushButtonSolve_2->setDisabled(true);
        break;
    case 2:
        ui->pushButtonSolve_2->setText("Stop");
        ui->pushButtonRead->setDisabled(true);
        ui->pushButtonSolve->setDisabled(true);
        break;
    }
}

void AntColonyDialog::enableForm()
{
    ui->lineEditSeed->setDisabled(false);
    ui->lineEditPopulation->setDisabled(false);
    ui->lineEditGenerations->setDisabled(false);
    ui->lineEditQProb->setDisabled(false);
    ui->lineEditQ->setDisabled(false);
    ui->lineEditMods->setDisabled(false);
    ui->lineEditEvaporation->setDisabled(false);
    ui->lineEditInflunce->setDisabled(false);
    ui->comboBoxThreads->setDisabled(false);
    ui->comboBoxSeeds->setDisabled(false);
    if(ui->pushButtonSolve->text() == "Stop")
    {
        ui->pushButtonSolve->setText("Batch Solve");
        ui->pushButtonRead->setDisabled(false);
        ui->pushButtonSolve_2->setDisabled(false);
    }
    else if(ui->pushButtonSolve_2->text() == "Stop")
    {
        ui->pushButtonSolve_2->setText("Test");
        ui->pushButtonRead->setDisabled(false);
        ui->pushButtonSolve->setDisabled(false);
    }
    else
    {
        ui->pushButtonRead->setText("Solve");
        ui->pushButtonSolve->setDisabled(false);
        ui->pushButtonSolve_2->setDisabled(false);
    }
    if(done == 1)
    {
        ui->pushButtonRead->setText("Close");
    }
}

void AntColonyDialog::newProblem(int thread, QString fileName, int percent)
{
    labels[thread*2+1]->setText(fileName);
    if(percent > ui->progressBar->value())
    {
        ui->progressBar->setValue(percent);
    }
}

void AntColonyDialog::problemEnded(QString stuff, int ended)
{
    stream << stuff << endl;
    if(ended == 1){
        enableForm();
        timer.stop();
        ui->progressBar->setValue(100);
    }
}

void AntColonyDialog::update()
{
    int time = elapsed.elapsed()/1000;
    int seconds = time%60;
    QString strsec="";
    if(seconds < 10){
        strsec += "0";
    }
    strsec += QString::number(seconds);
    int minutes = (time%3600-seconds)/60;
    QString strmin;
    int hours = time/3600;
    if(hours > 0){
        strmin += "0" + QString::number(hours) + ":";
    }
    if(minutes < 10){
        strmin += "0";
    }
    strmin += QString::number(minutes);
    ui->labelElapsed->setText("Elapsed Time: " + strmin + ":" + strsec);
}


