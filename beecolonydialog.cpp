#include "beecolonydialog.h"
#include "ui_beecolonydialog.h"

BeeColonyDialog::BeeColonyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BeeColonyDialog)
{
    ui->setupUi(this);

    for(int i = QThread::idealThreadCount(); i > 0 ; i--)
    {
        ui->comboBoxThreads->addItem(QString::number(i));
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

BeeColonyDialog::~BeeColonyDialog()
{
    delete ui;
}

void BeeColonyDialog::clearLayout(){
    QLayoutItem *child;
    while ((child = ui->gridLayout->takeAt(0)) != 0)
    {
        if (child->widget())
        {
            delete child->widget();
        }
        if (child->layout())
        {
            delete child->layout();
        }
        delete child;
    }
}

void BeeColonyDialog::enableGraph()
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

void BeeColonyDialog::enableThreads(){
    if(previous == 0)
    {
        done = 1;
    }
    previous = 1;
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
    for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
    {
        if(i < (ui->comboBoxThreads->currentText().toInt()+1)/2)
        {
            labels << new QLabel("Thread " + QString::number(i));
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 1, i*2+1);
            labels << new QLabel("File");
            labels[labels.length()-1]->setAlignment(Qt::AlignCenter);
            ui->gridLayout->addWidget(labels[labels.length()-1], 2, i*2+1);
        }else
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

void BeeColonyDialog::on_pushButtonRead_clicked()
{
    if(ui->pushButtonRead->text() == "Solve")
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open txt"), "../RLP_Qt/DataSets", tr("Text Files (*.txt)"));
        if(fileName != "")
        {
            enableGraph();
            elapsed.start();
            connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
            timer.start(1000);
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

void BeeColonyDialog::on_pushButtonSolve_clicked()
{
    if(ui->pushButtonSolve->text() == "Batch Solve")
    {
        QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/DataSets");
        if(dir.dirName() != ".")
        {
            ui->progressBar->setValue(0);
            enableThreads();
            QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_bee_colony_settings_" + ui->comboBoxSeeds->currentText() + ".txt");
            info.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream infoStream(&info);
            infoStream << "Population: " <<  ui->lineEditPopulation->text() << endl;
            infoStream << "Generations: " <<  ui->lineEditGenerations->text() << endl;
            infoStream << "Select Size: " <<  ui->lineEditSelectSize->text() << endl;
            infoStream << "Best Size: " <<  ui->lineEditBestSize->text() << endl;
            infoStream << "Select Value: " <<  ui->lineEditSelectValue->text() << "%" << endl;
            infoStream << "Best Value: " <<  ui->lineEditBestValue->text() << "%" << endl;
            infoStream << "Change Value: " <<  ui->lineEditChangeValue->text() << endl;
            info.close();

            file.setFileName("../RLP_Qt/DataSets/" + dir.dirName() + "_bee_colony_" + ui->comboBoxSeeds->currentText() + ".csv");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            stream.setDevice(&file);
            stream << "sep=;" << endl;
            stream << "Size;Problem;Instance;Seed;Generations;Time;Fitness;Regenerators;Disconnected" << endl;
            threads.clear();
            elapsed.start();
            connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
            timer.start(1000);
            for(int i = 0; i < ui->comboBoxThreads->currentText().toInt(); i++)
            {
                threads << new BeeColonyMultiThread(dir, ui->comboBoxSeeds->currentText().split("-")[0].toInt(),
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
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Please select a directory.");
            msgBox.addButton("Whatever", QMessageBox::AcceptRole);
            msgBox.exec();
        }
    }
    else
    {
        for(int i = 0; i < threads.length(); i++)
        {
            threads[i]->terminate();
        }
        enableForm();
        file.close();
        timer.stop();
    }
}

void BeeColonyDialog::singleProblem(QString stuff){
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

void BeeColonyDialog::onDataChanged(QString stuff)
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
    }
    ui->progressBar->setValue(moreStuff[5].toInt());
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
    ui->comboBoxThreads->setDisabled(true);
    ui->comboBoxSeeds->setDisabled(true);
    if(batch == 1)
    {
        ui->pushButtonSolve->setText("Stop");
        ui->pushButtonRead->setDisabled(true);
    }
    else
    {
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
    ui->comboBoxThreads->setDisabled(false);
    ui->comboBoxSeeds->setDisabled(false);
    if(ui->pushButtonSolve->text() == "Stop")
    {
        ui->pushButtonSolve->setText("Batch Solve");
        ui->pushButtonRead->setDisabled(false);
    }
    else
    {
        ui->pushButtonRead->setText("Solve");
        ui->pushButtonSolve->setDisabled(false);
    }
    if(done == 1)
    {
        ui->pushButtonRead->setText("Close");
    }
}

void BeeColonyDialog::newProblem(int thread, QString fileName, int percent)
{
    labels[thread*2+1]->setText(fileName);
    if(percent > ui->progressBar->value())
    {
        ui->progressBar->setValue(percent);
    }
}

void BeeColonyDialog::problemEnded(QString stuff, int ended)
{
    stream << stuff << endl;
    if(ended == 1)
    {
        enableForm();
        ui->progressBar->setValue(100);
    }
}

void BeeColonyDialog::update()
{
    int time = elapsed.elapsed()/1000;
    int seconds = time%60;
    QString strsec="";
    if(seconds < 10)
    {
        strsec += "0";
    }
    strsec += QString::number(seconds);
    int minutes = (time%3600-seconds)/60;
    QString strmin;
    int hours = time/3600;
    if(hours > 0)
    {
        strmin += "0" + QString::number(hours) + ":";
    }
    if(minutes < 10)
    {
        strmin += "0";
    }
    strmin += QString::number(minutes);
    ui->labelElapsed->setText("Elapsed Time: " + strmin + ":" + strsec);
}
