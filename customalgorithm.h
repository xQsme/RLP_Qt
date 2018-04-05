#ifndef CUSTOMALGORITHM_H
#define CUSTOMALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"


class CustomAlgorithm : public GeneticAlgorithm
{
public:
    CustomAlgorithm();
    void setUpAlgorithm(int generation, int elitism, int mutation, int generations);
    int generateNewPopulation(Population* population, Problem* problem);
    float getElitism();
    float getMutation();
private:
    float elitism;
    float mutation;
};

#endif // CUSTOMALGORITHM_H
