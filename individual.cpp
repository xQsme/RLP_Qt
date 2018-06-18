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

int Individual::calculateFitness(Problem* problem)
{
    QVector<QVector<int>> nodes = problem->getNodes();
    QVector<int> weights = problem->getWeights();
    fitness=0;
    disconnected=0;
    regenerators=0;
    int match;
    for (int i = 0; i < solution.length(); i++) {
        match = 0;
        for (int j = 0; j < solution.length(); j++) {
            if (nodes[i][j] == 1) {
                if (solution[j] == 1) {
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
    for (int i = 0; i < solution.length(); i++) {
        if (solution[i] == 1) {
            regenerators++; //guarda o total de regeneradores
            if(problem->hasWeights() == 1){
                fitness += 100 * weights[i];
            }else{
                fitness += 100;
            }
        }
    }
    return fitness;
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

void Individual::addValue(int i)
{
    solution << i;
}

void Individual::invertValue(int pos)
{
    solution[pos]=qAbs(solution[pos]-1);
}
