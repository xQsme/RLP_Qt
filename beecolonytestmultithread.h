#ifndef BEECOLONYTESTMULTITHREAD_H
#define BEECOLONYTESTMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "beecolonyalgorithm.h"

class BeeColonyTestMultiThread : public QThread
{
    Q_OBJECT
public:
    BeeColonyTestMultiThread();
    BeeColonyTestMultiThread(QString dir, int seed, int populationSize, int generations, int selectSize, int bestSize,
                             int selectStart, int selectEnd, int selectIncrement, int bestStart, int bestEnd,
                             int bestIncrement, int changeStart, int changeEnd, int changeIncrement, int thread, int threads);
    void run();
private:
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int selectSize;
    int bestSize;
    int selectStart;
    int selectEnd;
    int selectIncrement;
    int bestStart;
    int bestEnd;
    int bestIncrement;
    int changeStart;
    int changeEnd;
    int changeIncrement;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // BEECOLONYMULTITHREAD_H
