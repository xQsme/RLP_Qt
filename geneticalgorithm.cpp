#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::setUpAlgorithm(int generations){
    this->generation=0;
    this->generations=generations;
}

int GeneticAlgorithm::getGeneration()
{
    return generation;
}

int GeneticAlgorithm::getGenerations()
{
    return generations;
}
