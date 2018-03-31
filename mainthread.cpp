#include "mainthread.h"

MainThread::MainThread()
{

}

MainThread::MainThread(Population* population, Problem* problem)
{
    this->population=population;
    this->problem=problem;
}

void MainThread::run()
{
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

