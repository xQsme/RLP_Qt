#include "antcolonythread.h"

AntColonyThread::AntColonyThread()
{

}

AntColonyThread::AntColonyThread(QString fileName, int seed, int populationSize, int generations, double probability_q,
                                 double q, int number_mods, double evaporation, double influence)
{
    this->fileName=fileName;
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->probability_q=probability_q;
    this->q=q;
    this->number_mods=number_mods;
    this->evaporation=evaporation;
    this->influence=influence;
}


void AntColonyThread::run()
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
    algorithm.setUpAlgorithm(generations, probability_q, q, number_mods, &population, &problem, evaporation, influence);
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
                QString::number(algorithm.getGeneration()) + " " + ended + " " +
                QString::number(100*algorithm.getGeneration()/algorithm.getGenerations());

        emit dataChanged(stuff);
    }
}

