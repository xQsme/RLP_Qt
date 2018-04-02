#include "multithread.h"

MultiThread::MultiThread()
{

}

MultiThread::MultiThread(Population* population, Problem* problem, int thread, int threadCount, QVector<QMutex>* mutexes)
{
    this->population=population;
    this->problem=problem;
    this->thread=thread;
    this->threadCount=threadCount;
    this->mutexes=mutexes;
}

void MultiThread::run()
{
    while(population->generateNewPopulation(/*thread, threadCount*/) == 1){
        //mutexes->operator [](thread).lock();
        if(thread == threadCount-1){
            for(int i=0; i<threadCount; i++){
                /*if(mutexes->operator [](i)){

                }*/
            }
            population->calculateFitnesses(problem);
            QString ended;
            if(population->getGeneration() >= population->getGenerations()){
                ended = " 1";
            }else{
                ended = " 0";
            }
            QString stuff = QString::number(population->getBestIndividual().getFitness()) + " " +
                    QString::number(population->getBestIndividual().getDisconnected()) + " " +
                    QString::number(population->getBestIndividual().getRegenerators()) + " " +
                    QString::number(population->getGeneration()) + ended;
            emit dataChanged(stuff);
        }
    }
}

