#ifndef BEECOLONYALGORITHM_H
#define BEECOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"


class BeeColonyAlgorithm : public GeneticAlgorithm
{
public:
    BeeColonyAlgorithm();
    void setUpAlgorithm(int generation, int generations);
    int generateNewPopulation(Population* population, Problem* problem);
private:
};

#endif // BEECOLONYALGORITHM_H
