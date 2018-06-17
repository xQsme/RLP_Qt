#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "customalgorithm.h"

class CustomThread : public QThread
{
    Q_OBJECT
public:
    CustomThread();
    CustomThread(QString fileName, int seed, int populationSize, int generations, int elitism, int mutation);
    void run();
private:
    Population population;
    Problem problem;
    CustomAlgorithm algorithm;
    QString fileName;
    int seed;
    int populationSize;
    int generations;
    int elitism;
    int mutation;
signals:
    void dataChanged(QString stuff);
    void singleProblem(QString stuff);
    void wrongFile();
};

#endif // CUSTOMTHREAD_H
