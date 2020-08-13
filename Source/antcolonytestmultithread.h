#ifndef ANTCOLONYTESTMULTITHREAD_H
#define ANTCOLONYTESTMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "antcolonyalgorithm.h"

class AntColonyTestMultiThread : public QThread
{
    Q_OBJECT
public:
    AntColonyTestMultiThread();
    AntColonyTestMultiThread(QString dir, int seed, int populationSize, int generations, int Q, int startQprob, int endQprob, int incrementQprob, int startMods, int endMods, int incrementMods,
                          int startEvaporation, int endEvaporation, int incrementEvaporation, int startInfluence, int endInfluence, int incrementInfluence,
                          int thread, int threads);

    void run();
private:
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int Q;
    int startQprob;
    int endQprob;
    int incrementQprob;
    int startMods;
    int endMods;
    int incrementMods;
    int startEvaporation;
    int endEvaporation;
    int incrementEvaporation;
    int startInfluence;
    int endInfluence;
    int incrementInfluence;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
    void wrongFile();
};

#endif // ANTCOLONYMULTITHREAD_H
