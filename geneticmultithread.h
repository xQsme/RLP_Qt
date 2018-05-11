#ifndef GENETICMULTITHREAD_H
#define GENETICMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "geneticalgorithm.h"

class GeneticMultiThread : public QThread
{
    Q_OBJECT
public:
    GeneticMultiThread();
    GeneticMultiThread(QString dir, int seed, int populationSize, int generations, int elitism, int mutation, int thread, int threads);
    void run();
private:
    QString getFileInfo(QString file);
    QString getSeedString(int seed);
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
#endif // GENETICMULTITHREAD_H
