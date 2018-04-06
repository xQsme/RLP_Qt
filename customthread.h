#ifndef MAINTHREAD_H
#define MAINTHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"
#include "customalgorithm.h"

class CustomThread : public QThread
{
    Q_OBJECT
public:
    CustomThread();
    CustomThread(Population* population, Problem* problem, CustomAlgorithm* algorithm);
    void run();
private:
    Population* population;
    Problem* problem;
    CustomAlgorithm* algorithm;
signals:
    void dataChanged(QString);
};

#endif // MAINTHREAD_H
