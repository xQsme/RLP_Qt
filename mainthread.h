#ifndef MAINTHREAD_H
#define MAINTHREAD_H
#include <QtCore>
#include "population.h"
#include "problem.h"

class MainThread : public QThread
{
    Q_OBJECT
public:
    MainThread();
    MainThread(Population population, Problem problem);
    void run();
private:
    Population population;
    Problem problem;
signals:
    void dataChanged(QString);
};

#endif // MAINTHREAD_H
