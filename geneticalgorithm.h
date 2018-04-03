#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <QTcore>
#include <QVector>
#include "problem.h"
#include "population.h"


class GeneticAlgorithm
{
public:
    GeneticAlgorithm();
    void setUpAlgorithm(int elitism, int mutation, int generations);
    int generateNewPopulation(Population* population, Problem* problem);
    int getGeneration();
    int getGenerations();
    int getElitism();
    int getMutation();
private:
    float elitism;
    float mutation;
    int generation;
    int generations;
};

#endif // GENETICALGORITHM_H
