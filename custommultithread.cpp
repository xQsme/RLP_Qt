#include "custommultithread.h"

CustomMultiThread::CustomMultiThread()
{

}

CustomMultiThread::CustomMultiThread(QDir dir, int seed, int populationSize, int generations, int elitism, int mutation)
{
    this->dir=dir;
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->elitism=elitism;
    this->mutation=mutation;
    this->timer.start();
}

void CustomMultiThread::run()
{
    QFile info("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm_settings.csv");
    info.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream infoStream(&info);
    infoStream << "Seed: " << QString::number(seed) << endl;
    infoStream << "Population: " <<  QString::number(populationSize) << endl;
    infoStream << "Generations: " <<  QString::number(generations) << endl;
    infoStream << "Elitism: " <<  QString::number(elitism) << "%" << endl;
    infoStream << "Mutation: " <<  QString::number(mutation) << "%" << endl;
    info.close();

    QFile file("../RLP_Qt/DataSets/" + dir.dirName() + "_custom_algorithm.csv");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream;
    stream.setDevice(&file);
    stream << "File;Generations;Time;Fitness;Regenerators;Disconnected" << endl;
    Problem problem;
    Population population;
    CustomAlgorithm algorithm;
    int previousFitness;
    int bestGeneration;
    int bestTime;
    int count=0;
    int total=dir.entryInfoList().length()-2;

    foreach(QFileInfo fileFromDir, dir.entryInfoList())
    {
        if(!dir.absolutePath().contains(fileFromDir.absoluteFilePath()))
        {
            count++;
            previousFitness=999999;
            bestGeneration=0;
            bestTime=0;
            try
            {
                problem.setUpProblem(fileFromDir.absoluteFilePath());
            }
            catch(const std::invalid_argument ex){
                return;
            }
            population.setUpPopulation(seed, populationSize, &problem);
            population.calculateFitnesses(&problem);
            algorithm.setUpAlgorithm(0, elitism, mutation, generations);
            emit newProblem(QString::number(problem.getTotal()) + " " + QString::number(problem.getConnections()) + " " +
                            QString::number(population.getBestIndividual().getFitness()) + " " +
                            QString::number(population.getBestIndividual().getDisconnected()) + " " +
                            QString::number(population.getBestIndividual().getRegenerators()));
            while(algorithm.generateNewPopulation(&population, &problem) == 1)
            {
                population.calculateFitnesses(&problem);
                if(previousFitness > population.getBestIndividual().getFitness()){
                    previousFitness = population.getBestIndividual().getFitness();
                    bestGeneration = algorithm.getGeneration();
                    bestTime = timer.elapsed();
                }
                QString ended;
                if(count >= total){
                    ended = " 1";
                }else{
                    ended = " 0";
                }
                emit dataChanged(QString::number(population.getBestIndividual().getFitness()) + " " +
                                 QString::number(population.getBestIndividual().getDisconnected()) + " " +
                                 QString::number(population.getBestIndividual().getRegenerators()) + " " +
                                 QString::number(algorithm.getGeneration()) + " " +
                                 QString::number(timer.elapsed()/1000) + ended + " " + QString::number(1.0*count/total));
            }
            stream << fileFromDir.fileName() << ";" << QString::number(bestGeneration) << ";" + QString::number(bestTime) << ";" <<
                                              QString::number(population.getBestIndividual().getFitness()) << ";" <<
                                              QString::number(population.getBestIndividual().getRegenerators()) << ";" <<
                                              QString::number(population.getBestIndividual().getDisconnected()) << endl;
        }
    }
    file.close();
}

