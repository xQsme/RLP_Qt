#ifndef ANTCOLONYALGORITHM_H
#define ANTCOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "problem.h"
#include "population.h"


class AntColonyAlgorithm
{
public:
    AntColonyAlgorithm();
    void setUpAlgorithm(int generations, double probability_q,
                        double q, int number_mods, Population* population,
                        Problem* problem, double evaporation, double influence);
    int generateNewPopulation(Population* population, Problem* problem);
    int getGeneration();
    int getGenerations();
    int getGenerationsWithoutImprovements();
private:
    void initializePheromoneTrail();
    void evaluate();
    void updatePheromoneTrail();
    int generation;
    int generations;
    int numberOfAnts; //nr total de individuos
    int individualSize; //tamanho de um individuo
    int generationBestAntRun; //geracao com a melhor ant run
    int generationsWithoutImprovments; //geracoes que se passaram desde a ultima melhoria
    int numberOfMods;
    bool intensification;
    double probability_q;
    double Q;
    double pheromoneEvaportaion;
    double pheromoneInfluence;
    double ***t; //trilho feromonal
    Population* ants;
    Individual bestAntIteration;
    Individual bestAntRun;
    Problem* problem;
};

#endif // ANTCOLONYALGORITHM_H
