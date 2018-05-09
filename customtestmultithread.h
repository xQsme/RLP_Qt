#ifndef CUSTOMTESTMULTITHREAD_H
#define CUSTOMTESTMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "customalgorithm.h"

class CustomTestMultiThread : public QThread
{
    Q_OBJECT
public:
    CustomTestMultiThread();
    CustomTestMultiThread(QDir dir, int seed, int populationSize, int generations, int startElitism, int endElitism,
                          int incrementElitism, int startMutation, int endMutation, int incrementMutation, int thread, int threads);
    void run();
private:
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int startElitism;
    int endElitism;
    int incrementElitism;
    int startMutation;
    int endMutation;
    int incrementMutation;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // CUSTOMMULTITHREAD_H
