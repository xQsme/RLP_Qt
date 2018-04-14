#include "beecolonymultithread.h"

BeeColonyMultiThread::BeeColonyMultiThread()
{

}

BeeColonyMultiThread::BeeColonyMultiThread(QDir dir, int seed, int populationSize, int generations, int selectSize, int bestSize, int selectValue, int bestValue, int changeValue, int thread, int threads)
{
    this->dir=dir;
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->selectSize=selectSize;
    this->bestSize=bestSize;
    this->selectValue=selectValue;
    this->bestValue=bestValue;
    this->changeValue=changeValue;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
    this->timer.start();
}

void BeeColonyMultiThread::run()
{
    Problem problem;
    Population population;
    BeeColonyAlgorithm algorithm;
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
                algorithm.setUpAlgorithm(selectSize, &problem, &population, selectSize, bestSize, selectValue, bestValue, changeValue);
                int value;
                if(thread == 0){
                    value = threads-1;
                }else{
                    value = thread-1;
                }
                emit newProblem(value, fileFromDir.fileName(), 100*count/total);
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
                if(count >= total){
                    ended = 1;
                }else{
                    ended = 0;
                }
                emit problemEnded(fileFromDir.fileName() + ";" + QString::number(bestGeneration) + ";" + QString::number(bestTime) + ";" +
                                                  QString::number(population.getBestIndividual().getFitness()) + ";" +
                                                  QString::number(population.getBestIndividual().getRegenerators()) + ";" +
                                                  QString::number(population.getBestIndividual().getDisconnected()), ended);
            }
        }
    }
}

