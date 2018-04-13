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
    void setUpAlgorithm(int generation, int generations, double probability_q,
                        double Q, int numberOfMods, Population* population, Problem* problem);
    int generateNewPopulation(Population* population, Problem* problem);
    void initializePheromoneTrail(void);
    int random(int low, int high);
    void evaluate();
private:
    int numberOfAnts; //nr total de individuos
    int individualSize; //tamanho de um individuo
    int generationBestAntRun; //geracao com a melhor ant run
    int generationsWithoutImprovments; //geracoes que se passaram desde a ultima melhoria
    int numberOfMods;
    bool intensification;
    double probability_q;
    double Q;
    QVector<QVector<QVector<double>>> t; //trilho feromonal
    Population* ants;
    Individual bestAntIteration;
    Individual bestAntRun;
    Problem* problem;
};

#endif // ANTCOLONYALGORITHM_H
