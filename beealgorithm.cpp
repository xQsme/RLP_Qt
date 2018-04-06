#include "beealgorithm.h"

BeeAlgorithm::BeeAlgorithm()
{

}

void BeeAlgorithm::setUpAlgorithm(int generation, int generations)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
}

int BeeAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    return 0;
}
