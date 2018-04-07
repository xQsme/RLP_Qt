#include "antcolonyalgorithm.h"

AntColonyAlgorithm::AntColonyAlgorithm()
{

}

void AntColonyAlgorithm::setUpAlgorithm(int generation, int generations, double probabilidade_q,
                                        double Q, int numberOfMods, Population* population)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
    this->probabilidade_q = probabilidade_q;
    this->Q = Q;
    this->numberOfAnts = population->getPopulationSize();
    this->individualSize = population->getBestIndividual().getSolution().length();
    this->bestAntFitness = population->getBestIndividual().getFitness();
    this->numberOfMods = numberOfMods;

    //iniciar o pheromonal trail
    for(int i=0; i<numberOfAnts; i++){
        t << QVector<QVector<double>>();
        for(int j = 0; j < individualSize; j++)
        {
            t[i] << QVector<double>();
        }
    }
}

int AntColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    bool cond;
    int i;
    Individual auxIndividual;

    if(generation++ >= generations)
    {
        return 0;
    }

    initializePheromoneTrail();

    cond=true;
    for(i = 0; i < numberOfAnts; i++)
    {
        auxIndividual = population->getIndividuals()[i].clone(individualSize);
    }

    return 0;
}

void AntColonyAlgorithm::initializePheromoneTrail()
{
    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                t[a][i] << 1.0/(Q*bestAntFitness);
            }
        }
    }
}
