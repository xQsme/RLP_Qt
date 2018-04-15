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
    void setUpAlgorithm(int generations);
    int getGeneration();
    int getGenerations();
private:
    int generation;
    int generations;
};

#endif // GENETICALGORITHM_H
