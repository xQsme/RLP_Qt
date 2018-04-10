#ifndef BEECOLONYTHREAD_H
#define BEECOLONYTHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "beecolonyalgorithm.h"

class BeeColonyThread : public QThread
{
    Q_OBJECT
public:
    BeeColonyThread();
    BeeColonyThread(Population* population, Problem* problem, BeeColonyAlgorithm* algorithm);
    void run();
private:
    Population* population;
    Problem* problem;
    BeeColonyAlgorithm* algorithm;
    QElapsedTimer timer;
signals:
    void dataChanged(QString);
};

#endif // BEECOLONYTHREAD_H
