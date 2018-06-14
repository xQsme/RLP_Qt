#include "genetictestmultithread.h"

GeneticTestMultiThread::GeneticTestMultiThread()
{

}

GeneticTestMultiThread::GeneticTestMultiThread(QString dir, int seed, int populationSize, int generations, int startElitism, int endElitism, int incrementElitism, int startMutation, int endMutation, int incrementMutation, int startRecombination, int endRecombination, int incrementRecombination,int startTournament, int endTournament, int incrementTournament,int thread, int threads)
{
    this->dir=QDir(dir);
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->startElitism=startElitism;
    this->endElitism=endElitism;
    this->incrementElitism=incrementElitism;
    this->startMutation=startMutation;
    this->endMutation=endMutation;
    this->incrementMutation=incrementMutation;
    this->startRecombination=startRecombination;
    this->endRecombination=endRecombination;
    this->incrementRecombination=incrementRecombination;
    this->startTournament=startTournament;
    this->endTournament=endTournament;
    this->incrementTournament=incrementTournament;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
}

void GeneticTestMultiThread::run()
{
    Problem problem;
    Population population;
    GeneticAlgorithm algorithm;
    int previousFitness;
    int bestGeneration;
    int bestTime;
    int count=0;
    int total=dir.entryInfoList().length()-2;
    QElapsedTimer currentTimer;
    currentTimer.start();

    foreach(QFileInfo fileFromDir, dir.entryInfoList())
    {
        if(!dir.absolutePath().contains(fileFromDir.absoluteFilePath()))
        {
            count++;
            if(count % threads == thread)
            {
                for(int elitism = startElitism; elitism <= endElitism; elitism+=incrementElitism)
                {
                    for(int mutation = startMutation; mutation <= endMutation; mutation+=incrementMutation)
                    {
                        for(int recombination = startRecombination; recombination <= endRecombination; recombination+=incrementRecombination)
                        {
                            for(int tournament = startTournament; tournament <= endTournament; tournament+=incrementTournament)
                            {
                                currentTimer.restart();
                                previousFitness=999999;
                                bestGeneration=0;
                                bestTime=0;
                                try
                                {
                                    problem.setUpProblem(fileFromDir.absoluteFilePath());
                                }
                                catch(const std::invalid_argument ex){
                                    return;
                                }
                                population.setUpPopulation(seed, populationSize, &problem);
                                population.calculateFitnesses(&problem);
                                algorithm.setUpAlgorithm(elitism, mutation, generations, recombination, tournament);
                                int value;
                                if(thread == 0){
                                    value = threads-1;
                                }else{
                                    value = thread-1;
                                }
                                if(elitism == startElitism && mutation == startMutation && recombination == startRecombination && tournament == startTournament)
                                {
                                    emit newProblem(value, fileFromDir.fileName(), 100*count/total);
                                }
                                while(algorithm.generateNewPopulation(&population, &problem) == 1)
                                {
                                    population.calculateFitnesses(&problem);
                                    if(previousFitness > population.getBestIndividual().getFitness()){
                                        previousFitness = population.getBestIndividual().getFitness();
                                        bestGeneration = algorithm.getGeneration();
                                        bestTime = currentTimer.elapsed();
                                    }
                                    QString ended;
                                    if(count >= total && algorithm.getGeneration() >= algorithm.getGenerations()){
                                        ended = " 1";
                                    }else{
                                        ended = " 0";
                                    }
                                }
                                int ended;
                                if(count >= total && elitism == endElitism && mutation == endMutation && recombination == endRecombination && tournament == endTournament){
                                    ended = 1;
                                }else{
                                    ended = 0;
                                }
                                emit problemEnded(QString::number(elitism) + ";" + QString::number(mutation) + ";" +
                                                                  QString::number(recombination) + ";" + QString::number(tournament) + ";" +
                                                                  QString::number(bestGeneration) + ";" + QString::number(bestTime) + ";" +
                                                                  QString::number(population.getBestIndividual().getRegenerators()) + ";" +
                                                                  QString::number(population.getBestIndividual().getDisconnected()), ended);
                            }
                        }
                    }
                }
            }
        }
    }
}

