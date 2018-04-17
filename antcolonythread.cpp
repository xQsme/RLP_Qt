#include "antcolonythread.h"

AntColonyThread::AntColonyThread()
{

}

AntColonyThread::AntColonyThread(Population* population, Problem* problem, AntColonyAlgorithm* algorithm)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
    this->timer.start();
}

void AntColonyThread::run()
{
    while(algorithm->generateNewPopulation(population, problem) == 1){
        //population->calculateFitnesses(problem); feito no algoritmo
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

