#ifndef CUSTOMALGORITHM_H
#define CUSTOMALGORITHM_H
#include <QTcore>
#include <QVector>
#include "problem.h"
#include "population.h"


class CustomAlgorithm
{
public:
    CustomAlgorithm();
    void setUpAlgorithm(int elitism, int mutation, int generations);
    int generateNewPopulation(Population* population, Problem* problem);
    int getGeneration();
    int getGenerations();
private:
    int generation=0;
    int generations;
    float elitism;
    float mutation;
};

#endif // CUSTOMALGORITHM_H
