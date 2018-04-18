#include "beecolonyalgorithm.h"

BeeColonyAlgorithm::BeeColonyAlgorithm()
{

}

void BeeColonyAlgorithm::setUpAlgorithm(int generations, Problem* problem, Population* population,
                                        int selectedSize, int bestSize, int valueSelection, int valueBest,
                                        int changeValue)
{
    this->generation=0;
    this->generations=generations;
    this->problem=problem;
    this->scoutBees = population;
    this->selectedSize=selectedSize; //mSelBees
    this->bestSize=bestSize; //eBestBees
    this->valueSelection=valueSelection; //n_mSelBees
    this->valueBest=valueBest; //n_eBestBees
    this->changeValue = changeValue;
    this->bestBeeIteration = Individual(problem);
    this->bestBeeRun = Individual(problem);
    evaluate();
}

int BeeColonyAlgorithm::generateNewPopulation(Population* population, Problem* problem)
{
    if(generation++ >= generations)
    {
        return 0;
    }

    int number;
    Individual selected;

    createSelectedBeePopulation();
    calculateBestBeesProbability();
    calculateSelBeesProbability();

    for (int i = 0; i < selectedSize; i++)
    {
        if (i < bestSize )
        {
             number=prob[i]*valueBest;
        }
        else
        {
            number=prob[i]*valueSelection;
        }
        for (int j = 0; j< number; j++)
        {
            selected = optimizeSolution(selBees.getIndividuals()[i].clone()); //TO-DO
            if ((selected.getFitness() < scoutBees->getIndividuals()[i].getFitness()) || (qrand() % 100 < qrand() % 100 && selected.getFitness()==scoutBees->getIndividuals()[i].getFitness()))
            {
                scoutBees->setIndividual(i, selected);
                selBees.setIndividual(i, selected);
            }
        }
    }
    for(int i = selectedSize; i < population->getPopulationSize(); i++){
        scoutBees->setIndividual(i, Individual(problem));
    }

    evaluate();

    return 1;
}

void BeeColonyAlgorithm::createSelectedBeePopulation()
{
    selBees.clearIndividuals();
    QVector<Individual> individuals = scoutBees->getIndividuals();
    for (int i = 0; i < selectedSize; i++)
    {
        selBees.addIndividual(individuals[i].clone());
    }
}

void BeeColonyAlgorithm::evaluate()
{
    scoutBees->calculateFitnesses(problem);
    bestBeeIteration = scoutBees->getBestIndividual().clone();

    if (generation == 0 || bestBeeRun.getFitness() > bestBeeIteration.getFitness())
    {
       bestBeeRun = bestBeeIteration.clone();
       generationBestBeeRun = generation;
    }
}

void BeeColonyAlgorithm::calculateBestBeesProbability()
{
    double totalFitness=0;
    QVector<Individual> individuals = selBees.getIndividuals();
    prob.clear();
    if (bestSize==1)
    {
        prob << 1;
    }
    else
    {
        for (int i = 0; i < bestSize; i++)
        {
            totalFitness+=individuals[i].getFitness();
        }
        for (int i = 0; i < bestSize; i++)
        {
            prob << (totalFitness-individuals[i].getFitness())/totalFitness;
        }
    }
}

void BeeColonyAlgorithm::calculateSelBeesProbability()
{
    double totalFitness=0;
    QVector<Individual> individuals = selBees.getIndividuals();
    if (selectedSize-bestSize==1)
    {
        prob << 1;
    }
    else
    {
        for (int i = bestSize; i < selectedSize; i++)
        {
            totalFitness+=individuals[i].getFitness();
        }
        for (int i = bestSize; i < selectedSize; i++)
        {
            prob << (totalFitness-individuals[i].getFitness())/totalFitness;
        }
    }
}

void BeeColonyAlgorithm::initializeProbabilities()
{
    for (int i = 0; i < selectedSize; i++)
    {
        prob << 0;
    }
}

Individual BeeColonyAlgorithm::optimizeSolution(Individual individual)
{
    Individual toReturn = individual.clone();
    QVector<float> weights = problem->getConnectionsWeight();

    for(int i = 0; i < changeValue; i++)
    {
        if(qrand() % 3 == 0){
            toReturn = individual.clone();
        }
        QVector<int> bestIndexes;
        QVector<float> bestValues;
        QVector<int> worstIndexes;
        QVector<float> worstValues;
        for(int k = 0; k < i*2+1; k++){
            if(k <= toReturn.getRegenerators()){
                worstIndexes << 0;
                worstValues << 1;
            }
            if(k <= problem->getTotal() - toReturn.getRegenerators()){
                bestIndexes << 0;
                bestValues << 0;
            }
        }
        for(int j = 0; j < weights.length(); j++){
            for(int k = 0; k < worstIndexes.length(); k++){
                if(toReturn.getSolution()[j] == 1)
                {
                    if(weights[j] < worstValues[k])
                    {
                        worstIndexes[k] = j;
                        worstValues[k] = weights[j];
                        break;
                    }
                }
            }
            for(int k = 0; k < worstIndexes.length(); k++){
                if(toReturn.getSolution()[j] == 0)
                {
                    if(weights[j] > bestValues[k])
                    {
                        bestIndexes[k] = j;
                        bestValues[k] = weights[j];
                        break;
                    }
                }
            }
        }
        if(qrand() % 2 == 0)
        {
            toReturn.setValue(bestIndexes[qrand() % bestIndexes.length()], 1);
        }
        else
        {
            toReturn.setValue(worstIndexes[qrand() % worstIndexes.length()], 0);
        }
        if(toReturn.calculateFitness(problem) < individual.getFitness())
        {
            return toReturn;
        }
    }

    return individual;
}

int BeeColonyAlgorithm::getGeneration()
{
    return generation;
}

int BeeColonyAlgorithm::getGenerations()
{
    return generations;
}


