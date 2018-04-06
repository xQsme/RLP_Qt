#ifndef BEEALGORITHMTHREAD_H
#define BEEALGORITHMTHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"
#include "beealgorithm.h"

class BeeAlgorithmThread : public QThread
{
    Q_OBJECT
public:
    BeeAlgorithmThread();
    BeeAlgorithmThread(Population* population, Problem* problem, BeeAlgorithm* algorithm);
    void run();
private:
    Population* population;
    Problem* problem;
    BeeAlgorithm* algorithm;
signals:
    void dataChanged(QString);
};

#endif // BEEALGORITHMTHREAD_H
