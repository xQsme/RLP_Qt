#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <QtCore>
#include <QVector>
#include "problem.h"
#include "population.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm();
    void setUpAlgorithm(int elitism, int mutation, int generations, int recombination, int tournament);
    int generateNewPopulation(Population* population, Problem* problem);
    int getGeneration();
    int getGenerations();
private:
    Individual tournament(QVector<Individual> individuals);
    int generation;
    int generations;
    float elitism;
    float mutation;
    float recombination;
    int tournamentSize;
};

#endif // GENETICALGORITHM_H
