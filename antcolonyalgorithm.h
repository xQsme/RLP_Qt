#ifndef ANTCOLONYALGORITHM_H
#define ANTCOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"


class AntColonyAlgorithm : public GeneticAlgorithm
{
public:
    AntColonyAlgorithm();
<<<<<<< HEAD
    void setUpAlgorithm(int generation, int generations, double probability_q,
                        double Q, int numberOfMods, Population* population);
    int generateNewPopulation(Population* population, Problem* problem);
    void initializePheromoneTrail(void);
    int random(int low, int high);
    void evaluate(Population *ants);
=======
    void setUpAlgorithm(int generation, int generations, double probabilidade_q,
                        double Q, int numberOfMods, Population* population);
    int generateNewPopulation(Population* population, Problem* problem);
    void initializePheromoneTrail();
>>>>>>> 48f8a530ffbf12c47da2e8dd872c7a8a0c5f55ed
private:
    int numberOfAnts; //nr total de individuos
    int individualSize; //tamanho de um individuo
    double probability_q;
    double Q;
    QVector<QVector<QVector<double>>> t; //trilho feromonal
    int bestAntFitness; //fitness da melhor formiga
    int numberOfMods;
};

#endif // ANTCOLONYALGORITHM_H
