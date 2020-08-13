#include "beecolonythread.h"

BeeColonyThread::BeeColonyThread()
{

}

BeeColonyThread::BeeColonyThread(QString fileName, int seed, int populationSize, int generations, int selectSize, int bestSize, int selectValue, int bestValue, int changeValue)
{
    this->fileName=fileName;
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->selectSize=selectSize;
    this->bestSize=bestSize;
    this->selectValue=selectValue;
    this->bestValue=bestValue;
    this->changeValue=changeValue;
}

void BeeColonyThread::run()
{
    try
    {
        problem.setUpProblem(fileName);
    }
    catch(const std::invalid_argument ex){
        emit wrongFile();
        return;
    }
    population.setUpPopulation(seed, populationSize, &problem);
    population.calculateFitnesses(&problem);
    algorithm.setUpAlgorithm(generations, &problem, &population, selectSize, bestSize, selectValue, bestValue, changeValue);
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
            ended = " 1 ";
        }else{
            ended = " 0 ";
        }
        stuff = QString::number(population.getBestIndividual().getFitness()) + " " +
                QString::number(population.getBestIndividual().getDisconnected()) + " " +
                QString::number(population.getBestIndividual().getRegenerators()) + " " +
                QString::number(algorithm.getGeneration()) + ended +
                QString::number(100*algorithm.getGeneration()/algorithm.getGenerations());

        emit dataChanged(stuff);
    }
}

