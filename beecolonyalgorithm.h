#ifndef BEECOLONYALGORITHM_H
#define BEECOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "problem.h"
#include "population.h"

class BeeColonyAlgorithm
{
public:
    BeeColonyAlgorithm();
    void setUpAlgorithm(int generations, Problem* problem, Population* population,
                         int selectedSize, int bestSize, int valueSelection, int valueBest,
                         int changeValue);
    int generateNewPopulation(Population* population, Problem* problem);
    int getGeneration();
    int getGenerations();
private:
    int generation=0;
    int generations;
    void createSelectedBeePopulation();
    void evaluate();
    void calculateBestBeesProbability();
    void calculateSelBeesProbability();
    void initializeProbabilities();
    Individual optimizeSolution(Individual individual);
    Problem* problem;
    Population* scoutBees;
    Population selBees;
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
