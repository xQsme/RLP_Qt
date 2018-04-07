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
    this->individualSize = population->getBestIndividual().solution.length();
    this->bestAntFitness = population->getBestIndividual().getFitness();
    this->numberOfMods = numberOfMods;

    //iniciar o pheromonal trail
    t = new double**[numberOfAnts];
    for(int j = 0; j < numberOfAnts; j++)
    {
        t[j]=new double*[individualSize];
        for(int i = 0; i < individualSize; i++)
        {
            t[j][i] = new double[2];
        }
    }
}

int AntColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    bool cond;
    int i;
    Individual *auxIndividual;

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

void AntColonyAlgorithm::initializePheromoneTrail(void)
{
    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                t[a][i][j]=1.0/(Q*bestAntFitness);
            }
        }
    }
}
