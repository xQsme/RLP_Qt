#include "beecolonyalgorithm.h"

BeeColonyAlgorithm::BeeColonyAlgorithm()
{

}

void BeeColonyAlgorithm::setUpAlgorithm(int generation, int generations)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
}

int BeeColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    return 0;
}
