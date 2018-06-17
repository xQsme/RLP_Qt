#ifndef GENETICTESTMULTITHREAD_H
#define GENETICTESTMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "geneticalgorithm.h"

class GeneticTestMultiThread : public QThread
{
    Q_OBJECT
public:
    GeneticTestMultiThread();
    GeneticTestMultiThread(QString dir, int seed, int populationSize, int generations, int startElitism, int endElitism,
                          int incrementElitism, int startMutation, int endMutation, int incrementMutation,
                          int startRecombination, int endRecombination, int incrementRecombination,int startTournament,
                          int endTournament, int incrementTournament, int thread, int threads);
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
    int startRecombination;
    int endRecombination;
    int incrementRecombination;
    int startTournament;
    int endTournament;
    int incrementTournament;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
    void wrongFile();
};

#endif // GENETICMULTITHREAD_H
