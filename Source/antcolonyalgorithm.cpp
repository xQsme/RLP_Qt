#include "antcolonyalgorithm.h"

AntColonyAlgorithm::AntColonyAlgorithm()
{

}

void AntColonyAlgorithm::setUpAlgorithm(int generations, double probability_q,
                                        double q, int number_mods, Population* population,
                                        Problem* problem, double evaporation,
                                        double influence)
{
    this->generations=generations;
    this->problem = problem;
    this->ants = population;
    this->probability_q = probability_q;
    this->Q = q;
    this->numberOfAnts = population->getPopulationSize();
    this->individualSize = population->getBestIndividual().getSolution().size();
    this->numberOfMods = number_mods;
    this->bestAntIteration = Individual(problem);
    this->bestAntRun = Individual(problem);
    this->pheromoneEvaportaion = evaporation;
    this->pheromoneInfluence = influence;
    this->generationsWithoutImprovments = 0;
    this->generation = 0;

    //iniciar o pheromonal trail
    t.clear();
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
    if(generation++ >= generations)
    {
        return 0;
    }

    bool cond;
    int i, n, s, r, j, novo;
    double maior, total, soma, probability;
    Individual auxIndividual;

    cond=true;
    for(i = 0; i < ants->getPopulationSize(); i++) //Para cada individuo/formiga
    {
        auxIndividual = population->getIndividuals()[i].clone(); //clona essa formiga

        for(n = 0; n < numberOfMods; n++) //Para cada modificao pretendida
        {
            if((qrand() % 100) < probability_q) //probability [0;100]
            {
                maior = 0;
                s = 0;
                r = qrand() % (individualSize);

                for(j = 0; j < 2; j++)
                {
                    if(t[i][r][j] > maior) //ver se o 1 ou o 0 é melhor
                    {
                        maior = t[i][r][j];
                        s = j;
                    }
                }
                // altera o valor desse elemento do individuo

                auxIndividual.setValue(r,s);
            }
            else
            {
                //exploration
                //faz mutações
                r=qrand() % (individualSize);
                total = 0;
                soma = 0;
                for(j = 0; j < 2; j++)
                {
                    total += t[i][r][j];
                }
                probability = (qrand() % 100)/100.0;
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
                // altera o valor desse elemento do individuo

                auxIndividual.setValue(r,novo);
            }
        }
        auxIndividual.calculateFitness(problem);
        if(intensification == true) //se a intensificacao estiver ativa
        {
            //se o fitness do individuo atual for menor que o já existente, substitui
            if(auxIndividual.getFitness() <= ants->getIndividuals()[i].getFitness())
            {
                ants->setIndividual(i, auxIndividual);
                cond = false;
            }
        }
        else
        {
            ants->setIndividual(i, auxIndividual);
        }
    }
    //BUSCA LOCAL
    //1)
    //passar os nós a 1 para zero e testar sempre
    //se a solucao for uma das solucoes possiveis
    //só testando uma vez cada um e verificar de cada

    //2)
    //tentar verificar pares que não estão concectados
    //e tentar verificar se inserindo 1 é possivel

    //3)
    //Se um deles estiver conectado a mais que um regenerador, tentar tirar

    //4)
    //Tentar trocar duas posicaoes aleatoriamente e verificar se ha melhoria


    ants->calculateFitnesses(problem);
    Individual lsIndividual;
    for(int ind = 0; ind < ants->getPopulationSize();ind++)
    {
        lsIndividual = ants->getIndividuals()[ind].clone();
        for(int o = 0; o < lsIndividual.getSolution().length(); o++)
        {
            lsIndividual.invertValue(o);
            lsIndividual.calculateFitness(problem);

            if(lsIndividual.getFitness() <= ants->getIndividuals()[ind].getFitness())
            {
                ants->setIndividual(ind, lsIndividual);
                ants->getIndividuals()[ind].calculateFitness(problem);
            }else{
                lsIndividual.invertValue(o);
            }
        }
    }

    //se não foi possivel melhorar nenhuma solucao
    if(cond)
    {
        intensification = false;
    }

    //avalia novamente, caso encontre uma solucao melhor ativa a intensificacao
    evaluate();
    generationsWithoutImprovments++;

    updatePheromoneTrail();

    //se ocorrem demasiadas geracoes sem que haja uma melhoria? Aplicar ou Não?

    return 1;
}

void AntColonyAlgorithm::initializePheromoneTrail()
{
    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                t[a][i] << 1.0/(Q*bestAntIteration.getFitness()); //Q is [0;100]?
            }
        }
    }
}

int AntColonyAlgorithm::getGenerationsWithoutImprovements()
{
    return generationsWithoutImprovments;
}

void AntColonyAlgorithm::updatePheromoneTrail()
{
    int g;

    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                t[a][i][j] = (1.0 - (pheromoneEvaportaion * 0.01)) * t[a][i][j]; //pheromoneEvaportaion is [0;1]
            }
        }
    }
    for(int a = 0; a < numberOfAnts; a++)
    {
        for(int i = 0; i < individualSize; i++)
        {
            if(bestAntIteration.getSolution()[i] != 0)
            {
                g = 1;
            }
            else
            {
                g = 0;
            }

            t[a][i][g]=t[a][i][g]+((pheromoneInfluence * 0.01)/bestAntIteration.getFitness()); //pheromoneInfluence is [0;1]
        }
    }
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

int AntColonyAlgorithm::getGeneration()
{
    return generation;
}

int AntColonyAlgorithm::getGenerations()
{
    return generations;
}
