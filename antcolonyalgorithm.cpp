#include "antcolonyalgorithm.h"

AntColonyAlgorithm::AntColonyAlgorithm()
{

}

void AntColonyAlgorithm::setUpAlgorithm(int generation, int generations)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
}

int AntColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    return 0;
}
