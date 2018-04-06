#include "beecolonythread.h"

BeeColonyThread::BeeColonyThread()
{

}

BeeColonyThread::BeeColonyThread(Population* population, Problem* problem, BeeColonyAlgorithm* algorithm)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
}

void BeeColonyThread::run()
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

