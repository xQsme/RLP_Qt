#ifndef GENETICTHREAD_H
#define GENETICTHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"
#include "geneticalgorithm.h"

class GeneticThread : public QThread
{
    Q_OBJECT
public:
    GeneticThread();
    GeneticThread(QString fileName, int seed, int populationSize, int generations, int elitism, int mutation, int recombination, int tournament);
    void run();
private:
    Population population;
    Problem problem;
    GeneticAlgorithm algorithm;
    QString fileName;
    int seed;
    int populationSize;
    int generations;
    int elitism;
    int mutation;
    int recombination;
    int tournament;
signals:
    void dataChanged(QString stuff);
    void singleProblem(QString stuff);
};

#endif // GENETICTHREAD_H
