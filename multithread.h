#ifndef MULTITHREAD_H
#define MULTITHREAD_H
#include <QtCore>
#include <QVector>
#include <QMutex>
#include "population.h"
#include "problem.h"
#include "geneticalgorithm.h"

class MultiThread : public QThread
{
    Q_OBJECT
public:
    MultiThread();
    MultiThread(Population* population, Problem* problem, GeneticAlgorithm* algorithm, int thread, int threadCount, QVector<QMutex>* mutexes);
    void run();
private:
    Population* population;
    Problem* problem;
    GeneticAlgorithm* algorithm;
    int thread;
    int threadCount;
    QVector<QMutex>* mutexes;

signals:
    void dataChanged(QString);
};

#endif // MULTITHREAD_H
