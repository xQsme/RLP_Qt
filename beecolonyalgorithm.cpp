#include "beecolonyalgorithm.h"

BeeColonyAlgorithm::BeeColonyAlgorithm()
{

}

void BeeColonyAlgorithm::setUpAlgorithm(int generation, int generations, Problem* problem, Population* population,
                                        int selectedSize, int bestSize, int valueSelection, int valueBest,
                                        int changeValue)
{
    GeneticAlgorithm::setUpAlgorithm(generation, generations);
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

    QVector<Individual> individuals = scoutBees->getIndividuals();
    for (int i = 0; i < population->getPopulationSize(); i++)
    {
        population->setIndividual(i, search.apply(problem, individuals[i])); //TO-DO
    }

    evaluate();
    createSelectedBeePopulation();
    calculateBestBeesProbability();
    calculateSelBeesProbability();

    QVector<Individual> selIndividuals = selBees.getIndividuals();
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
            selected = optimizeSolution(selIndividuals[i].clone()); //TO-DO
            if ((selected.getFitness() < individuals[i].getFitness()) || (qrand() % 100 < qrand() % 100 && selected.getFitness()==individuals[i].getFitness()))
            {
                scoutBees->setIndividual(i, selected);
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
    Individual toReturn = individual;

    return toReturn;
}

