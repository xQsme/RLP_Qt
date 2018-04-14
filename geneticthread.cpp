#include "geneticthread.h"

GeneticThread::GeneticThread()
{

}

GeneticThread::GeneticThread(Population* population, Problem* problem, GeneticAlgorithm* algorithm)
{
    this->population=population;
    this->problem=problem;
    this->algorithm=algorithm;
}

void GeneticThread::run()
{

}

