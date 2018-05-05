#ifndef ANTCOLONYMULTITHREAD_H
#define ANTCOLONYMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "antcolonyalgorithm.h"

class AntColonyMultiThread : public QThread
{
    Q_OBJECT
public:
    AntColonyMultiThread();
    AntColonyMultiThread(QDir dir, int seed, int populationSize, int generations, int probability_q, int q, int number_mods, int evaporation, int influence, int thread, int threads);
    void run();
private:
    QString getFileInfo(QString file);
    QString getSeedString(int seed);
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    double probability_q;
    double q;
    int number_mods;
    double evaporation;
    double influence;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // ANTCOLONYMULTITHREAD_H
