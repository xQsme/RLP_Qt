#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <QVector>
#include "problem.h"

class Individual
{
public:
    Individual();
    Individual(int nodes);
    void calculateFitness(Problem problem);
    QVector<int> getSolution();
    int getFitness();
    int getDisconnected();
    int getRegenerators();
    int setValue(int index, int value);
    int setFitness(int fitness);
    int setDisconnected(int disconnected);
    int setRegenerators(int regenerators);
private:
    QVector<int> solution;
    int fitness=0;
    int disconnected=0;
    int regenerators=0;
};

#endif // INDIVIDUAL_H
