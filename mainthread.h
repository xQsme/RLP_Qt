#ifndef MAINTHREAD_H
#define MAINTHREAD_H
#include <QtCore>
#include <QVector>
#include <QMutex>
#include "population.h"
#include "problem.h"
#include "geneticalgorithm.h"
#include "customalgorithm.h"
#include "multithread.h"

class MainThread : public QThread
{
    Q_OBJECT
public:
    MainThread();
    MainThread(Population* population, Problem* problem, CustomAlgorithm* algorithm/*, int threads*/);
    void run();
private:
    Population* population;
    Problem* problem;
    CustomAlgorithm* algorithm;
/*    int threadCount;
    QVector<MultiThread> threads;
    QVector<QMutex> mutexes;*/
signals:
    void dataChanged(QString);
/*public slots:
    void onDataChanged(QString);*/
};

#endif // MAINTHREAD_H
