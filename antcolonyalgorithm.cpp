#include "antcolonyalgorithm.h"

AntColonyAlgorithm::AntColonyAlgorithm()
{

}

void AntColonyAlgorithm::setUpAlgorithm(int generation, int generations, double probability_q,
                                        double Q, int numberOfMods, Population* population, Problem* problem)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
    this->problem = problem;
    this->ants = population;
    this->probability_q = probability_q;
    this->Q = Q;
    this->numberOfAnts = population->getPopulationSize();
    this->individualSize = population->getBestIndividual().getSolution().length();
    this->numberOfMods = numberOfMods;
    this->bestAntIteration = Individual(problem);
    this->bestAntRun = Individual(problem);
    generationsWithoutImprovments = 0;

    //iniciar o pheromonal trail
    for(int i=0; i<numberOfAnts; i++){
        t << QVector<QVector<double>>();
        for(int j = 0; j < individualSize; j++)
        {
            t[i] << QVector<double>();
        }
    }

    evaluate(); //procura a melhor solucao
    initializePheromoneTrail(); //inicia o trilho de feromonas
    intensification = true;
}

int AntColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    bool cond;

    int i, n, s, r, j, novo;
    double maior, total, soma, probability;
    Individual auxIndividual;

    if(generation++ >= generations)
    {
        return 0;
    }

    cond=true;
    for(i = 0; i < ants->getPopulationSize(); i++) //Para cada individuo/formiga
    {
        auxIndividual = population->getIndividuals()[i].clone(); //clona essa formiga

        for(n = 0; n < numberOfMods; n++) //Para cada modificao pretendida
        {
            if(((qrand() / 101)/100) < probability_q)
            {
                maior = 0;
                s = 0;
                r = qrand() / individualSize + 1;
                for(j = 0; j < 2; j++)
                {
                    if(t[i][r][j] > maior)
                    {
                        maior = t[i][r][j];
                        s = j;
                    }
                }

                if(s != 0)
                {
                    // what are demands??
                    // valor que o individuo assume na posicao?
                    //s = problem->getDemandValue(r);
                }
                // altera o valor desse elemento do individuo
                auxIndividual.setValue(r,s);
            }
            else
            {
                r=random(0, individualSize);
                total = 0;
                soma = 0;
                for(j = 0; j < 2; j++)
                {
                    total += t[i][r][j];
                }
                probability = random(0, 101)/100.0;
                novo=1;
                for(j = 0; j < 2; j++)
                {
                    soma += t[i][r][j] / total;
                    if(probability <= soma)
                    {
                        novo = j;
                        break;
                    }
                }
                if(novo != 0){
                    // get demand value???
                    // valor que o individuo assume na posicao?
                    // novo = problem->getDemandValue(r);
                }
                // altera o valor desse elemento do individuo
                auxIndividual.setValue(r,novo);
            }
        }

        //verifica se o fitness melhorou apos a mutacao
        if(auxIndividual.getFitness() <= population->getIndividuals()[i].getFitness())
        {
            //int idx = 0;

            //Este foreach causa varios erros, tentar arranjar alternativa
            //o que faz, é que se o fitness do individuo alterado for melhor que o do individuo original,
            //então substituimos o original pelo alterado
            /*
            foreach (int val, auxIndividual)
            {
                population->setValue(i, idx, val);
                idx++;
            }
            */
        }
        else
        {
            //both not work atm
            //auxIndividual.releaseMemory();
            //delete auxIndividual;
        }
        auxIndividual = population->getIndividuals()[i].clone();
    }

    evaluate(); //TODO
    return 0;
}

void AntColonyAlgorithm::initializePheromoneTrail()
{
    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                t[a][i] << 1.0/(Q*bestAntIteration.getFitness());
            }
        }
    }
}

int AntColonyAlgorithm::random(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void AntColonyAlgorithm::evaluate()
{
    ants->calculateFitnesses(problem);
    bestAntIteration = ants->getBestIndividual().clone();

    for (int i = 0; i < ants->getPopulationSize(); i++)
    {
        if (bestAntIteration.getFitness() > ants->getIndividuals()[i].getFitness())
        {
            bestAntIteration = ants->getIndividuals()[i].clone();
        }
    }

    if (generation == 0 || bestAntRun.getFitness() > bestAntIteration.getFitness())
    {
       bestAntRun = bestAntIteration.clone();
       generationBestAntRun = generation;

       //foi encontrada uma melhor solucao
       intensification=true;
       generationsWithoutImprovments = 0;
    }

}
