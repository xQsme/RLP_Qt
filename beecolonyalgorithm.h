#ifndef BEECOLONYALGORITHM_H
#define BEECOLONYALGORITHM_H
#include <QTcore>
#include <QVector>
#include "geneticalgorithm.h"
#include "problem.h"
#include "population.h"


class BeeColonyAlgorithm : public GeneticAlgorithm
{
public:
    BeeColonyAlgorithm();
    void setUpAlgorithm(int generation, int generations, Problem* problem, int nBees,
                        int mSelBees, int eBestBees, int n_mSelBees, int n_eBestBees,
                        int numeroModificacoes, int busca);
    int generateNewPopulation(Population* population, Problem* problem);
private:
    Population selBees, scoutBees;
    int busca; //Criar class descida
    int nBees, mSelBees, eBestBees, n_mSelBees, n_eBestBees;
    int tamanhoIndividuo;
    int numeroModificacoes;
    int iteracaoMelhorBeeRun;
    Individual melhorBeeIteracao;
    Individual melhorBeeRun;
    QVector<double> prob;
    QVector<int> sbees;
    QVector<double> anel;
    QVector<int> ntanel;
};

#endif // BEECOLONYALGORITHM_H
