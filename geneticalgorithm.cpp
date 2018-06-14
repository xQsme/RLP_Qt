#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::setUpAlgorithm(int elitism, int mutation, int generations, int recombination, int tournament)
{
    this->generation=0;
    this->generations=generations;
    this->elitism=elitism * 0.01;
    this->mutation=mutation * 0.01;
    this->recombination = recombination * 0.01;
    this->tournamentSize = tournament;
}

int GeneticAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    if(generation++ >= generations)
    {
        return 0;
    }

    QVector<Individual> individuals = population->getIndividuals();

    //Aplica o Elitismo
    int selected = elitism * individuals.length();
    Population populationAux;
    int solutionSize = individuals[1].getSolution().size();
    int nrIndividuals = individuals.size();

    //Guarda na PopulaçãoAux os melhores individuos
    for(int i=0; i<selected; i++)
    {
        populationAux.addIndividual(individuals[i]);
    }

    //Aplica o torneio aos restantes individuos
    for(int i=selected; i< nrIndividuals; i++)
    {
        populationAux.addIndividual(tournament(individuals));
    }

    individuals = populationAux.getIndividuals();

    //Recombinação 1 corte
    int cut; //local onde será o corte
    for(int j = 0; j < nrIndividuals-1; j+=2)
    {
        if(qrand() % 100 < (int)(1/recombination))
        {
            cut = qrand() % solutionSize;

            for(int n = 0; n < cut; n++)
            {
                individuals[j].setValue(n, individuals[j+1].getSolution()[n]);
            }
        }
    }

    //Mutação
    int newValue; //valor que ira ser colocado ao mutar
    for(int m = 0; m < nrIndividuals; m++)
    {
        for(int k = 0; k < solutionSize; k++)
        {
            //if(qrand() % (int)(1 / mutation) == 0)
            if(qrand() % 100 <= (int)(1/mutation))
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
    /*
    int index = 0;
    foreach(Individual ind, individuals)
    {
        populationAux.setIndividual(index,ind);
        index++;
    }
    populationAux.calculateFitnesses(problem);
    */
    for(int p=0; p<nrIndividuals; p++)
    {
        populationAux.setIndividual(p, individuals[p]);
    }
    populationAux.calculateFitnesses(problem);

    int index = 0;
    for(int i=selected;i<nrIndividuals;i++)
    {
        population->setIndividual(i,populationAux.getIndividual(index));
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
    //Vai buscar um individuo ao calhas
    Individual best = individuals[qrand() % individuals.size()];

    for(int i = 1; i < tournamentSize; i++)
    {
        //vai buscar outro individuo ao calhas
        Individual aux = individuals[qrand() % individuals.size()];
        //substitui sempre, caso o fitness seja melhor
        if(aux.getFitness() < best.getFitness()){
            best = aux;
        }
    }
    //devolve o vencedor do torneio
    return best.clone();
}
