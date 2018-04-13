#ifndef CUSTOMMULTITHREAD_H
#define CUSTOMMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "customalgorithm.h"

class CustomMultiThread : public QThread
{
    Q_OBJECT
public:
    CustomMultiThread();
    CustomMultiThread(Population* population, Problem* problem, CustomAlgorithm* algorithm, int count);
    void run();
private:
    Population* population;
    Problem* problem;
    CustomAlgorithm* algorithm;
    QElapsedTimer timer;
    int bestGeneration;
    int bestTime;
    int previousFitness=1000000;
    int count;
signals:
    void threadEnded(QString stuff, int count);
};

#endif // CUSTOMMULTITHREAD_H
