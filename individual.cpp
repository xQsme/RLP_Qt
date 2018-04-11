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


Individual Individual::clone(Problem* problem)
{
    Individual aux = Individual(problem);
    aux.setDisconnected(disconnected);
    aux.setFitness(fitness);
    aux.setRegenerators(regenerators);
    int idx = 0;
    foreach (int i, solution) {
        aux.setValue(idx++,i);
    }
    return aux;
}
