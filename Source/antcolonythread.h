#ifndef ANTCOLONYHREAD_H
#define ANTCOLONYTHREAD_H
#include <QtCore>
#include "population.h"
#include <QElapsedTimer>
#include "problem.h"
#include "antcolonyalgorithm.h"

class AntColonyThread : public QThread
{
    Q_OBJECT
public:
    AntColonyThread();
    AntColonyThread(QString fileName, int seed, int populationSize, int generations, int probability_q,
                                     int q, int number_mods, int evaporation, int influence);
    void run();
private:
    Population population;
    Problem problem;
    AntColonyAlgorithm algorithm;
    QString fileName;
    int seed;
    int populationSize;
    int generations;
    double probability_q;
    double q;
    int number_mods;
    double evaporation;
    double influence;
signals:
    void dataChanged(QString stuff);
    void singleProblem(QString stuff);
    void wrongFile();
};

#endif // ANTCOLONYTHREAD_H
