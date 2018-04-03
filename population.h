#ifndef POPULATION_H
#define POPULATION_H
#include "problem.h"
#include "individual.h"

class Population
{
public:
    Population();
    void setUpPopulation(int seed, int populationSize, Problem* problem);
    void calculateFitnesses(Problem* problem);
    QVector<Individual> getIndividuals();
    void setValue(int i, int j, int value);
    Individual getBestIndividual();
    int getPopulationSize();
    int getSeed();
private:
    QVector<Individual> individuals;
    int populationSize;
    int individualSize;
    int seed;
};

#endif // POPULATION_H
