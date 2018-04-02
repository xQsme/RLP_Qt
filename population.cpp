#include "population.h"

Population::Population()
{

}

void Population::setUpPopulation(int seed, int populationSize, int generations, int elitism, int mutation, Problem* problem)
{
    srand(seed);
    individuals.clear();
    for(int i = 0; i < populationSize; i++)
    {
        individuals << Individual(problem->getTotal());
    }
    this->generation=0;
    this->seed=seed;
    this->populationSize=populationSize;
    individualSize = problem->getTotal();
    this->generations=generations;
    this->elitism=elitism * 0.01;
    this->mutation=mutation * 0.01;
}

void Population::setUpPopulation(int generations, int elitism, int mutation)
{
    this->generations=generations;
    this->elitism=elitism * 0.01;
    this->mutation=mutation * 0.01;
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

int Population::generateNewPopulation(/*int thread, int threadCount*/)
{
    if(generation++ >= generations){
        return 0;
    }

    //Selected é o indice onde acabam os individuos que foram mantidos (Elitismo), estes não são alterados
    int selected = elitism * individuals.length();
    //Reprodução
    for (int i = selected; i < individuals.length(); i++) {
        for (int j = 0; j < individualSize; j++) {
            if (selected != 0) { //Para nao dividir por 0
                individuals[i].setValue(j, individuals[rand() % selected].getSolution()[j]);
                //cada nó dum individuo não selecionado, toma um valor dum nó dum individuo selecionado
            }
        }
    }
    //Mutação
    int zeroes, ones;
    for (int j = 0; j < individualSize; j++) {
        zeroes = ones = 0;
        for (int i = 0; i < selected; i++) {
            if (individuals[i].getSolution()[j] == 0) {
                zeroes++;
            }
            else {
                ones++;
            }
        }
        //A partir do selecionados até metade dos restantes
        //quando naquela coluna os selecionados apenas têm 1s
        if (zeroes == 0) {
            for (int i = selected; i < (individuals.length() - selected) / 2 + selected; i++) {
                if (rand() % (int)(1 / mutation) == 0) { //conforme a probabilidade de mutação
                    individuals[i].setValue(j, 0); //alguns nós passam a 0
                }
            }
        }
        //quando naquela coluna os selecionados apenas têm 0s
        if (ones == 0) {
            for (int i = selected; i < (individuals.length() - selected) / 2 + selected; i++) {
                if (rand() % (int)(1 / mutation) == 0) {
                    individuals[i].setValue(j, 1); //alguns nós passam a 1
                }
            }
        }

        //A partir de metade dos restantes até ao final da população
        for (int i = (individuals.length() - selected) / 2 + selected; i < individuals.length(); i++) {
            if (rand() % (int)(1 / mutation) == 0) { //Conforme a probabilidade de mutação
                individuals[i].setValue(j, rand() % 2); //É atribuido um valor 0 ou 1 random
            }
        }
    }

    return 1;
}

Individual Population::getBestIndividual()
{
    return individuals[0];
}

int Population::getGeneration()
{
    return generation;
}

int Population::getGenerations()
{
    return generations;
}

int Population::getPopulationSize()
{
    return populationSize;
}

int Population::getElitism()
{
    return (int) elitism*100;
}

int Population::getMutation()
{
    return (int) mutation*100;
}

int Population::getSeed()
{
    return seed;
}
