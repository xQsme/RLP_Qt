#include "beecolonyalgorithm.h"

BeeColonyAlgorithm::BeeColonyAlgorithm()
{

}

void BeeColonyAlgorithm::setUpAlgorithm(int generation, int generations, Problem* problem, int nBees,
                                        int mSelBees, int eBestBees, int n_mSelBees, int n_eBestBees,
                                        int numeroModificacoes, int busca)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
    this->nBees=nBees;
    this->mSelBees=mSelBees;
    this->eBestBees=eBestBees;
    this->n_mSelBees=n_mSelBees;
    this->n_eBestBees=n_eBestBees;
    this->numeroModificacoes = numeroModificacoes;
    this->busca= busca;
    this->melhorBeeIteracao = Individual(problem->getTotal());
    this->melhorBeeRun = Individual(problem->getTotal());
    this->tamanhoIndividuo = problem->getTotal();
}

int BeeColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    return 0;
}
