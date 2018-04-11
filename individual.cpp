#include "individual.h"

Individual::Individual()
{

}

Individual::Individual(Problem* problem)
{
    QVector<float> percentages = problem->getConnectionsWeight();
    for(int i = 0; i < problem->getTotal(); i++){
        if(qrand() % (int)(1 / percentages[i] * 2) == 0)
        {
            solution << 1;
        }
        else
        {
            solution << 0;
        }
    }
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


Individual Individual::clone()
{
    Individual aux = Individual();
    aux.setDisconnected(disconnected);
    aux.setFitness(fitness);
    aux.setRegenerators(regenerators);
    foreach (int i, solution) {
        aux.addValue(i);
    }
    return aux;
}

void Individual::addValue(int i){
    solution << i;
}
