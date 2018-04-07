#include "individual.h"

Individual::Individual()
{

}

Individual::Individual(int nodes)
{
    for(int i = 0; i < nodes; i++){
        solution << rand() % 2;
    }
}

//not sure if required for program to work
void Individual::releaseMemory()
{
    /*
    if(this->getSolution() != NULL)
    {
        free(this->getSolution());
    }

    this->getSolution() = NULL;
    */
}

QVector<int> Individual::getSolution(){
    return solution;
}

int Individual::getFitness(){
    return fitness;
}

int Individual::getDisconnected(){
    return disconnected;
}

int Individual::getRegenerators(){
    return regenerators;
}

void Individual::setValue(int index, int value)
{
    solution[index]=value;
}

void Individual::setFitness(int fitness)
{
    this->fitness=fitness;
}

void Individual::setDisconnected(int disconnected)
{
    this->disconnected=disconnected;
}

void Individual::setRegenerators(int regenerators)
{
    this->regenerators=regenerators;
}

Individual *Individual::clone(int nodes)
{
    /*
        int idx = 0;
        foreach (int z, auxIndividual->getSolution()) {
            auxIndividual->setValue(idx,z);
            idx++;
        }
     */

    return new Individual(nodes);
}
