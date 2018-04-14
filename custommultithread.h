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
    CustomMultiThread(QDir dir, int seed, int populationSize, int generations, int elitism, int mutation, int thread, int threads);
    void run();
private:
    QElapsedTimer timer;
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int elitism;
    int mutation;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // CUSTOMMULTITHREAD_H
