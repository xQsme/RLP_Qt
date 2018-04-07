#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::setUpAlgorithm(int generation, int generations){
    if(generation == 0){
        this->generation=generation;
    }
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
