#include "customthread.h"

CustomThread::CustomThread()
{

}

CustomThread::CustomThread(Population* population, Problem* problem, CustomAlgorithm* algorithm)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
    this->timer.start();
}

void CustomThread::run()
{
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
                QString::number(algorithm->getGeneration()) + " " +
                QString::number(timer.elapsed()/1000) + ended + " " +
                QString::number(100*algorithm->getGeneration()/algorithm->getGenerations());

        emit dataChanged(stuff);
    }
}

