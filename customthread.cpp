#include "customthread.h"

CustomThread::CustomThread()
{

}

CustomThread::CustomThread(QString fileName, int seed, int populationSize, int generations, int elitism, int mutation)
{
    this->fileName=fileName;
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->elitism=elitism;
    this->mutation=mutation;
}

void CustomThread::run()
{
    try
    {
        problem.setUpProblem(fileName);
    }
    catch(const std::invalid_argument ex){
        return;
    }
    population.setUpPopulation(seed, populationSize, &problem);
    population.calculateFitnesses(&problem);
    algorithm.setUpAlgorithm(elitism, mutation, generations);
    QString stuff = QString::number(population.getBestIndividual().getFitness()) + " " +
            QString::number(population.getBestIndividual().getDisconnected()) + " " +
            QString::number(population.getBestIndividual().getRegenerators()) + " " +
            QString::number(problem.getTotal()) + " " +
            QString::number(problem.getConnections());
    emit singleProblem(stuff);
    while(algorithm.generateNewPopulation(&population, &problem) == 1){
        population.calculateFitnesses(&problem);
        QString ended;
        if(algorithm.getGeneration() >= algorithm.getGenerations()){
            ended = " 1";
        }else{
            ended = " 0";
        }
        stuff = QString::number(population.getBestIndividual().getFitness()) + " " +
                QString::number(population.getBestIndividual().getDisconnected()) + " " +
                QString::number(population.getBestIndividual().getRegenerators()) + " " +
                QString::number(algorithm.getGeneration()) + ended + " " +
                QString::number(100*algorithm.getGeneration()/algorithm.getGenerations());

        emit dataChanged(stuff);
    }
}

