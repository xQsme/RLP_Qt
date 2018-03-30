#ifndef POPULATION_H
#define POPULATION_H
#include "problem.h"
#include "individual.h"

class Population
{
public:
    Population();
    void setUpPopulation(int seed, int populationSize, int generations, int elitism, int mutation, Problem problem);
    void calculateFitnesses();
    int generateNewPopulation();
    Individual getBestIndividual();
    int getGeneration();
private:
    Problem problem;
    QVector<Individual> individuals;
    int individualSize;
    float elitism;
    float mutation;
    int generation=0;
    int generations;
};

#endif // POPULATION_H
