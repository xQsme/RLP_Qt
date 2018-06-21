#include "customalgorithm.h"

CustomAlgorithm::CustomAlgorithm()
{

}

void CustomAlgorithm::setUpAlgorithm(int elitism, int mutation, int generations)
{
    this->generation=0;
    this->generations=generations;
    this->elitism=elitism * 0.01;
    this->mutation=mutation * 0.01;
}

int CustomAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    if(generation++ >= generations)
    {
        return 0;
    }
    QVector<Individual> individuals = population->getIndividuals();
    //Selected é o indice onde acabam os individuos que foram mantidos (Elitismo), estes não são alterados
    int selected = elitism * individuals.length();
    //Reprodução
    if (selected != 0) { //Para nao dividir por 0
        for (int i = selected; i < individuals.length(); i++)
        {
            for (int j = 0; j < problem->getTotal(); j++)
            {
                population->setValue(i, j, individuals[qrand() % selected].getSolution()[j]);
                //cada nó dum individuo não selecionado, toma um valor dum nó dum individuo selecionado
            }
        }
    }
    //Mutação
    int zeroes, ones;
    for (int j = 0; j < problem->getTotal(); j++)
    {
        zeroes = ones = 0;
        for (int i = 0; i < selected; i++)
        {
            if (individuals[i].getSolution()[j] == 0)
            {
                zeroes++;
            }
            else
            {
                ones++;
            }
        }
        //A partir do selecionados até metade dos restantes
        //quando naquela coluna os selecionados apenas têm 1s
        if (zeroes == 0)
        {
            for (int i = selected; i < (individuals.length() - selected) / 2 + selected; i++)
            {
                if (qrand() % (int)(1 / mutation) == 0)
                { //conforme a probabilidade de mutação
                    population->setValue(i, j, 0); //alguns nós passam a 0
                }
            }
        }
        //quando naquela coluna os selecionados apenas têm 0s
        if (ones == 0)
        {
            for (int i = selected; i < (individuals.length() - selected) / 2 + selected; i++)
            {
                if (qrand() % (int)(1 / mutation) == 0)
                {
                    population->setValue(i, j, 1); //alguns nós passam a 1
                }
            }
        }

        //A partir de metade dos restantes até ao final da população
        for (int i = (individuals.length() - selected) / 2 + selected; i < individuals.length(); i++)
        {
            if (qrand() % (int)(1 / mutation) == 0)
            { //Conforme a probabilidade de mutação
                population->setValue(i, j, qrand() % 2); //É atribuido um valor 0 ou 1 random
            }
        }
    }

    if (selected/2 != 0) { //Para nao dividir por 0
    //Recombinar a segunda metade dos selecionados com base na primeira metade
        for(int i=selected/2; i < selected; i++)
        {
            for (int j = 0; j < problem->getTotal(); j++)
            {
                population->setValue(i, j, individuals[qrand() % (selected/2)].getSolution()[j]);
                //cada nó dum individuo não selecionado, toma um valor dum nó dum individuo selecionado
            }
        }
    }

    population->calculateFitnesses(problem);

    return 1;
}

int CustomAlgorithm::getGeneration()
{
    return generation;
}

int CustomAlgorithm::getGenerations()
{
    return generations;
}
