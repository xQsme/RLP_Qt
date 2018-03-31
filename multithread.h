#ifndef MULTITHREAD_H
#define MULTITHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"

class MultiThread : public QThread
{
    Q_OBJECT
public:
    MultiThread();
    MultiThread(Population* population, Problem* problem);
    void run();
private:
    Population* population;
    Problem* problem;
signals:
    void dataChanged(QString);
};

#endif // MULTITHREAD_H
