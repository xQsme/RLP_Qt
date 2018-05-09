#ifndef BEECOLONYMULTITHREAD_H
#define BEECOLONYMULTITHREAD_H
#include <QtCore>
#include <QElapsedTimer>
#include "population.h"
#include "problem.h"
#include "beecolonyalgorithm.h"

class BeeColonyMultiThread : public QThread
{
    Q_OBJECT
public:
    BeeColonyMultiThread();
    BeeColonyMultiThread(QDir dir, int seed, int populationSize, int generations, int selectSize, int bestSize,
                         int selectValue, int bestValue, int changeValue, int thread, int threads);
    void run();
private:
    QString getFileInfo(QString file);
    QString getSeedString(int seed);
    QDir dir;
    int seed;
    int populationSize;
    int generations;
    int selectSize;
    int bestSize;
    int selectValue;
    int bestValue;
    int changeValue;
    int thread;
    int threads;
signals:
    void newProblem(int thread, QString fileName, int percent);
    void problemEnded(QString stuff, int ended);
};

#endif // BEECOLONYMULTITHREAD_H
