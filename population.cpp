#include "population.h"

Population::Population()
{

}

void Population::setUpPopulation(int seed, int populationSize, Problem* problem)
{
    srand(seed);
    individuals.clear();
    for(int i = 0; i < populationSize; i++)
    {
        individuals << Individual(problem->getTotal());
    }
    this->seed=seed;
    this->populationSize=populationSize;
    individualSize = problem->getTotal();
}

void Population::calculateFitnesses(Problem* problem)
{
    int fitness;
    int disconnected;
    int regenerators;
    QVector<int> currentSolution;
    QVector<int> weights;
    if(problem->hasWeights()){
        weights=problem->getWeights();
    }
    QVector<QVector<int>> nodes = problem->getNodes();

    int match;
    for(int ind = 0; ind < individuals.length(); ind++)
    {
        currentSolution = individuals[ind].getSolution();
        fitness=0;
        disconnected=0;
        regenerators=0;
        for (int i = 0; i < currentSolution.length(); i++) {
            match = 0;
            for (int j = 0; j < currentSolution.length(); j++) {
                if (nodes[i][j] == 1) {
                    if (currentSolution[j] == 1) {
                        match++;
                        break;
                    }
                }
            }
            if (match == 0) {
                disconnected++; //guarda o numero de ligações sem regenerador
                fitness+=500;
            }
        }
        for (int i = 0; i < currentSolution.length(); i++) {
            if (currentSolution[i] == 1) {
                regenerators++; //guarda o total de regeneradores
                if(problem->hasWeights() == 1){
                    fitness += 100 * weights[i];
                }else{
                    fitness += 100;
                }
            }
        }
        individuals[ind].setFitness(fitness);
        individuals[ind].setDisconnected(disconnected);
        individuals[ind].setRegenerators(regenerators);
    }

    //reorder individuals
    for (int i = 0; i < individuals.length(); i++) //Ordenar fitness crescente e população por fitness crescente
    {
        for (int j = 0; j < individuals.length() - 1; j++)
        {
            if (individuals[j].getFitness() > individuals[j + 1].getFitness()) //Se anterior maior que seguinte
            {
                Individual tempIndividual = individuals[j];
                individuals[j] = individuals[j + 1];
                individuals[j + 1] = tempIndividual; //seguinte passa a anterior
            }
        }
    }
}

void Population::setValue(int i, int j, int value){
    individuals[i].setValue(j, value);
}

void Population::clearIndividuals()
{
    individuals.clear();
}

void Population::addIndividual(Individual i)
{
    individuals << i;
}

QVector<Individual> Population::getIndividuals()
{
    return individuals;
}

Individual Population::getBestIndividual()
{
    return individuals[0];
}

int Population::getPopulationSize()
{
    return populationSize;
}

int Population::getSeed()
{
    return seed;
}
