#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <QVector>
#include "problem.h"

class Individual
{
public:
    Individual();
    Individual(int nodes);
    QVector<int> getSolution();
    int getFitness();
    int getDisconnected();
    int getRegenerators();
    void setValue(int index, int value);
    void setFitness(int fitness);
    void setDisconnected(int disconnected);
    void setRegenerators(int regenerators);
    void releaseMemory();
    Individual clone(int nodes);
private:
    QVector<int> solution;
    int fitness=0;
    int disconnected=0;
    int regenerators=0;
};

#endif // INDIVIDUAL_H
