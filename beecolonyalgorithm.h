#ifndef BEECOLONYALGORITHM_H
#define BEECOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"
#include "search.h"


class BeeColonyAlgorithm : public GeneticAlgorithm
{
public:
    BeeColonyAlgorithm();
    void setUpAlgorithm(int generation, int generations, Problem* problem, Population* population,
                         int selectedSize, int bestSize, int valueSelection, int valueBest,
                         int changeValue);
    int generateNewPopulation(Population* population, Problem* problem);
private:
    void createSelectedBeePopulation();
    void evaluate();
    void calculateBestBeesProbability();
    void calculateSelBeesProbability();
    void initializeProbabilities();
    Individual optimizeSolution(Individual individual);
    Problem* problem;
    Population* scoutBees;
    Population selBees;
    Search search;
    Individual bestBeeIteration;
    Individual bestBeeRun;
    QVector<double> prob;
    int selectedSize;
    int bestSize;
    int valueSelection;
    int valueBest;
    int changeValue;
    int generationBestBeeRun;
};

#endif // BEECOLONYALGORITHM_H
