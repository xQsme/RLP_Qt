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
    BeeColonyThread(QString fileName, int seed, int populationSize, int generations, int selectSize, int bestSize, int selectValue, int bestValue, int changeValue);
    void run();
private:
    Population population;
    Problem problem;
    BeeColonyAlgorithm algorithm;
    QString fileName;
    int seed;
    int populationSize;
    int generations;
    int selectSize;
    int bestSize;
    int selectValue;
    int bestValue;
    int changeValue;
signals:
    void dataChanged(QString stuff);
    void singleProblem(QString stuff);
    void wrongFile();
};

#endif // BEECOLONYTHREAD_H
