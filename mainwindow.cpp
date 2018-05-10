#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCustom_clicked()
{
    CustomDialog* dialog =  new CustomDialog();
    dialog->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::on_pushButtonAntColony_clicked()
{
    AntColonyDialog* dialog =  new AntColonyDialog();
    dialog->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::on_pushButtonBeeColony_clicked()
{
    BeeColonyDialog* dialog =  new BeeColonyDialog();
    dialog->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::on_pushButtonGeneticAlgorithm_clicked()
{
    GeneticDialog* dialog =  new GeneticDialog();
    dialog->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void MainWindow::on_actionSort_Results_triggered()
{
    QDir dir = QFileDialog::getExistingDirectory(0, ("Select Directory"), "../RLP_Qt/Results");
    if(dir.dirName() != ".")
    {
        foreach(QFileInfo fileToRead, dir.entryInfoList())
        {
            if(!dir.absolutePath().contains(fileToRead.absoluteFilePath()) && !fileToRead.fileName().contains("settings"))
            {
                QList<QString> list;
                QFile file(fileToRead.absoluteFilePath());
                file.open(QIODevice::ReadOnly | QIODevice::Text);
                while(!file.atEnd())
                {
                    list.append(file.readLine());
                }
                file.close();

                QString first = list.takeAt(0);
                QString second = list.takeAt(0);
                if(first.contains("sep=;") && second.contains("Size;Problem;Instance;Seed;Generations;Time;Fitness;Regenerators;Disconnected")){
                    list.sort();

                    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                    QTextStream in(&file);
                    in << first;
                    in << second;
                    for(int i = 0; i < list.length(); i++){
                        in << list.at(i);
                    }
                    file.close();
                }
            }
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("All files sorted.");
        msgBox.addButton("Whatever", QMessageBox::AcceptRole);
        msgBox.exec();
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
