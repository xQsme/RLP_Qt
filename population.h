#ifndef POPULATION_H
#define POPULATION_H
#include "problem.h"
#include "individual.h"

class Population
{
public:
    Population();
    void setUpPopulation(int seed, int populationSize, int generations, int elitism, int mutation, Problem* problem);
    void setUpPopulation(int generations, int elitism, int mutation);
    void calculateFitnesses(Problem* problem);
    int generateNewPopulation();
    Individual getBestIndividual();
    int getGeneration();
    int getGenerations();
    int getPopulationSize();
    int getElitism();
    int getMutation();
    int getSeed();
private:
    QVector<Individual> individuals;
    int populationSize;
    int individualSize;
    float elitism;
    float mutation;
    int generation;
    int generations;
    int seed;
};

#endif // POPULATION_H
