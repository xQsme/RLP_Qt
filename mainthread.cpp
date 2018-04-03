#include "mainthread.h"

MainThread::MainThread()
{

}

MainThread::MainThread(Population* population, Problem* problem/*, int threads*/)
{
    this->population=population;
    this->problem=problem;
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
    while(population->generateNewPopulation() == 1){
        population->calculateFitnesses(problem);
        QString ended;
        if(population->getGeneration() >= population->getGenerations()){
            ended = " 1";
        }else{
            ended = " 0";
        }
        QString stuff = QString::number(population->getBestIndividual().getFitness()) + " " +
                QString::number(population->getBestIndividual().getDisconnected()) + " " +
                QString::number(population->getBestIndividual().getRegenerators()) + " " +
                QString::number(population->getGeneration()) + ended;
        emit dataChanged(stuff);
    }
}

/*void MainThread::onDataChanged(QString stuff)
{
    emit dataChanged(stuff);
}*/
