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
    GeneticThread(Population* population, Problem* problem, GeneticAlgorithm* algorithm);
    void run();
private:
    Population* population;
    Problem* problem;
    GeneticAlgorithm* algorithm;
signals:
    void dataChanged(QString);
};

#endif // GENETICTHREAD_H
