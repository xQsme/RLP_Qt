#ifndef BEEALGORITHM_H
#define BEEALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"


class BeeAlgorithm : public GeneticAlgorithm
{
public:
    BeeAlgorithm();
    void setUpAlgorithm(int generation, int generations);
    int generateNewPopulation(Population* population, Problem* problem);
private:
};

#endif // BEEALGORITHM_H
