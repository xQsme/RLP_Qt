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

void Individual::calculateFitness(Problem problem)
{
    fitness=0;
    disconnected=0;
    regenerators=0;
    int match;
    for (int i = 0; i < problem.getTotal(); i++) {
        match = 0;
        for (int j = 0; j < problem.getTotal(); j++) {
            if (problem.getNodes()[i][j] == 1) {
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
            if(problem.hasWeights() == 1){
                fitness += 100 * problem.getWeights()[i];
            }else{
                fitness += 100;
            }
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

int Individual::setValue(int index, int value)
{
    solution[index]=value;
}
