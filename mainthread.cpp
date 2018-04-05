#include "mainthread.h"

MainThread::MainThread()
{

}

MainThread::MainThread(Population* population, Problem* problem, CustomAlgorithm* algorithm/*, int threads*/)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
    /*this->threadCount=threads;
    for(int i =0; i<threads; i++){
        mutexes << new QMutex();
        threads << new MultiThread(population, problem, i, threads, &mutexes);
    }
    connect(threads[threadCount-1], SIGNAL(dataChanged(QString)), this, SLOT(onDataChanged(QString)));*/
}

void MainThread::run()
{
    /*for(int i =0; i<threadCount; i++){
        threads[i].start();
    }*/
    while(algorithm->generateNewPopulation(population, problem) == 1){
        population->calculateFitnesses(problem);
        QString ended;
        if(algorithm->getGeneration() >= algorithm->getGenerations()){
            ended = " 1";
        }else{
            ended = " 0";
        }
        QString stuff = QString::number(population->getBestIndividual().getFitness()) + " " +
                QString::number(population->getBestIndividual().getDisconnected()) + " " +
                QString::number(population->getBestIndividual().getRegenerators()) + " " +
                QString::number(algorithm->getGeneration()) + ended;
        emit dataChanged(stuff);
    }
}

/*void MainThread::onDataChanged(QString stuff)
{
    emit dataChanged(stuff);
}*/
