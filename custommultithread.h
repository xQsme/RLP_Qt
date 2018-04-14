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
    CustomMultiThread(QDir dir, int seed, int populationSize, int generations, int elitism, int mutation);
    void run();
private:
    Population* population;
    Problem* problem;
    CustomAlgorithm* algorithm;
    QElapsedTimer timer;
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int elitism;
    int mutation;
signals:
    void dataChanged(QString stuff);
    void newProblem(QString stuff);
};

#endif // CUSTOMMULTITHREAD_H
