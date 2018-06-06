#ifndef BEECOLONYALGORITHM_H
#define BEECOLONYALGORITHM_H
#include <QtCore>
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
    void evaluate();
    void calculateBestBeesProbability();
    void calculateSelBeesProbability();
    void initializeProbabilities();
    Individual optimizeSolution(Individual individual);
    int generation;
    int generations;
    Problem* problem;
    Population* scoutBees;
    QVector<double> prob;
    int selectedSize;
    int bestSize;
    int valueSelection;
    int valueBest;
    int changeValue;
    int generationBestBeeRun;
};

#endif // BEECOLONYALGORITHM_H
