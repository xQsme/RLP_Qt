#include "antcolonytestmultithread.h"

AntColonyTestMultiThread::AntColonyTestMultiThread()
{

}

AntColonyTestMultiThread::AntColonyTestMultiThread(QString dir, int seed, int populationSize, int generations, int startQprob, int endQprob,
                                                   int incrementQprob, int startQ, int endQ, int incrementQ, int startMods, int endMods, int incrementMods,
                                                   int startEvaporation, int endEvaporation, int incrementEvaporation, int startInfluence, int endInfluence, int incrementInfluence,
                                                   int thread, int threads)
{
    this->dir=QDir(dir);
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->startQprob = startQprob;
    this->endQprob = endQprob;
    this->incrementQprob = incrementQprob;
    this->startQ = startQ;
    this->endQ = endQ;
    this->incrementQ = incrementQ;
    this->startMods = startMods;
    this->endMods = endMods;
    this->incrementMods = incrementMods;
    this->startEvaporation = startEvaporation;
    this->endEvaporation = endEvaporation;
    this->incrementEvaporation = incrementEvaporation;
    this->startInfluence = startInfluence;
    this->endInfluence = endInfluence;
    this->incrementInfluence = incrementInfluence;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
}

void AntColonyTestMultiThread::run()
{
    Problem problem;
    Population population;
    AntColonyAlgorithm algorithm;
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
                for(int qprob = startQprob; qprob <= endQprob; qprob+=incrementQprob)
                {
                    for(int q = startQ; q <= endQ; q+= incrementQ)
                    {
                        for(int mods = startMods; mods <= endMods; mods+=incrementMods)
                        {
                            for(int evaporation = startEvaporation; evaporation <= endEvaporation; evaporation+=incrementEvaporation)
                            {
                                for(int influence = startInfluence; influence <= endInfluence; influence+=incrementInfluence)
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
                                    algorithm.setUpAlgorithm(generations,qprob,q,mods,&population,&problem,evaporation,influence);
                                    int value;
                                    if(thread == 0){
                                        value = threads-1;
                                    }else{
                                        value = thread-1;
                                    }
                                    if(qprob == startQprob && q == startQ && mods == startMods && evaporation == startEvaporation && influence == startInfluence)
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
                                    if(count >= total && qprob == endQprob && q == endQ && mods == endMods && evaporation == endEvaporation && influence == endInfluence){
                                        ended = 1;
                                    }else{
                                        ended = 0;
                                    }
                                    emit problemEnded(QString::number(qprob) + ";" + QString::number(q) + ";" + QString::number(mods) + ";" +
                                                                      QString::number(evaporation) + ";" + QString::number(influence) + ";" +
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
}

