#include "custommultithread.h"

CustomMultiThread::CustomMultiThread()
{

}

CustomMultiThread::CustomMultiThread(Population* population, Problem* problem, CustomAlgorithm* algorithm, int count)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
    this->count=count;
    this->timer.start();

}

void CustomMultiThread::run()
{
    while(algorithm->generateNewPopulation(population, problem) == 1)
    {
        population->calculateFitnesses(problem);
        if(previousFitness > population->getBestIndividual().getFitness()){
            previousFitness = population->getBestIndividual().getFitness();
            bestGeneration = algorithm->getGeneration();
            bestTime = timer.elapsed();
        }
        if(algorithm->getGeneration() == algorithm->getGenerations())
        {
            emit threadEnded(QString::number(bestGeneration) + ";" + QString::number(bestTime) + ";" +
                             QString::number(population->getBestIndividual().getFitness()) + ";" +
                             QString::number(population->getBestIndividual().getRegenerators()) + ";" +
                             QString::number(population->getBestIndividual().getDisconnected()), count);
        }
    }
}

