#include "beecolonythread.h"

BeeColonyThread::BeeColonyThread()
{

}

BeeColonyThread::BeeColonyThread(Population* population, Problem* problem, BeeColonyAlgorithm* algorithm)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
    this->timer.start();
}

void BeeColonyThread::run()
{
    while(algorithm->generateNewPopulation(population, problem) == 1){
        QString ended;
        if(algorithm->getGeneration() >= algorithm->getGenerations()){
            ended = " 1";
        }else{
            ended = " 0";
        }
        QString stuff = QString::number(population->getBestIndividual().getFitness()) + " " +
                QString::number(population->getBestIndividual().getDisconnected()) + " " +
                QString::number(population->getBestIndividual().getRegenerators()) + " " +
                QString::number(algorithm->getGeneration()) + " " +
                QString::number(timer.elapsed()/1000) + ended;

        emit dataChanged(stuff);
    }
}

