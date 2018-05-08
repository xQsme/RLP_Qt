#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::setUpAlgorithm(int elitism, int mutation, int generations)
{
    this->generation=0;
    this->generations=generations;
    this->elitism=elitism * 0.01;
    this->mutation=mutation * 0.01;
}

int GeneticAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    if(generation++ >= generations)
    {
        return 0;
    }

    QVector<Individual> individuals = population->getIndividuals();

    int selected = elitism * individuals.length();

    //Seleção através de torneiro
    QVector<Individual> populationAux;
    for(int i=0; i<individuals.size(); i++)
    {
        populationAux.append(tournament(individuals));
    }

    //Recombinação Uniforme
    int recombinationProb = 70; //probabilidade de recombinar
    for(int j=selected; j< individuals.length(); j+=2)
    {
        if(qrand() % 100 < recombinationProb)
        {
            for(int n=0; n < individuals[j].getSolution().length(); n++)
            {
                //0 or 1 ?
                if(qrand() % 2 == 0 && n+1 != individuals[j].getSolution().length())
                {
                    individuals[j].setValue(n,individuals[j-selected].getSolution()[n]);
                }
            }
        }
    }

    //Mutação
    int newValue; //valor que ira ser colocado ao mutar
    for(int m = selected; m < individuals.size(); m++)
    {
        for(int k = 0; k < individuals[m].getSolution().size(); k++)
        {
            if(qrand() % (int)(1 / mutation) == 0)
            {
                if(individuals[m].getSolution()[k] != 1)
                {
                    newValue = 1;
                }
                else
                {
                    newValue = 0;
                }
                individuals[m].setValue(k, newValue);
            }
        }
    }

    int index = 0;
    foreach(Individual ind, individuals)
    {
        population->setIndividual(index,ind);
        index++;
    }
    population->calculateFitnesses(problem);

    return 1;
}

int GeneticAlgorithm::getGeneration()
{
    return generation;
}

int GeneticAlgorithm::getGenerations()
{
    return generations;
}

Individual GeneticAlgorithm::tournament(QVector<Individual> individuals)
{
    int size = 2; //tamanho do torneio
    //Vai buscar um individuo ao calhas
    Individual best = individuals[qrand() % individuals.size()];
    for(int i = 0; i < size; i++)
    {
        //vai buscar outro individuo ao calhas
        Individual aux = individuals[qrand() % individuals.size()];
        //substitui sempre, caso o fitness seja melhor
        if(aux.getFitness() > best.getFitness()){
            best = aux;
        }
    }
    //devolve o vencedor do torneio
    return best.clone();
}
