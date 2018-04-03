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
    if(generation++ >= generations){
        return 0;
    }
    QVector<Individual> individuals = population->getIndividuals();
    //Selected é o indice onde acabam os individuos que foram mantidos (Elitismo), estes não são alterados
    int selected = elitism * individuals.length();
    //Reprodução
    for (int i = selected; i < individuals.length(); i++) {
        for (int j = 0; j < problem->getTotal(); j++) {
            if (selected != 0) { //Para nao dividir por 0
                population->setValue(i, j, individuals[rand() % selected].getSolution()[j]);
                //cada nó dum individuo não selecionado, toma um valor dum nó dum individuo selecionado
            }
        }
    }
    //Mutação
    int zeroes, ones;
    for (int j = 0; j < problem->getTotal(); j++) {
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
                    population->setValue(i, j, 0); //alguns nós passam a 0
                }
            }
        }
        //quando naquela coluna os selecionados apenas têm 0s
        if (ones == 0) {
            for (int i = selected; i < (individuals.length() - selected) / 2 + selected; i++) {
                if (rand() % (int)(1 / mutation) == 0) {
                    population->setValue(i, j, 1); //alguns nós passam a 1
                }
            }
        }

        //A partir de metade dos restantes até ao final da população
        for (int i = (individuals.length() - selected) / 2 + selected; i < individuals.length(); i++) {
            if (rand() % (int)(1 / mutation) == 0) { //Conforme a probabilidade de mutação
                population->setValue(i, j, rand() % 2); //É atribuido um valor 0 ou 1 random
            }
        }
    }

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

int GeneticAlgorithm::getElitism()
{
    return (int) elitism*100;
}

int GeneticAlgorithm::getMutation()
{
    return (int) mutation*100;
}
