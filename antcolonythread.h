#ifndef ANTCOLONYHREAD_H
#define ANTCOLONYTHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"
#include "antcolonyalgorithm.h"

class AntColonyThread : public QThread
{
    Q_OBJECT
public:
    AntColonyThread();
    AntColonyThread(Population* population, Problem* problem, AntColonyAlgorithm* algorithm);
    void run();
private:
    Population* population;
    Problem* problem;
    AntColonyAlgorithm* algorithm;
signals:
    void dataChanged(QString);
};

#endif // ANTCOLONYTHREAD_H
