#include "beecolonytestmultithread.h"

BeeColonyTestMultiThread::BeeColonyTestMultiThread()
{

}

BeeColonyTestMultiThread::BeeColonyTestMultiThread(QString dir, int seed, int populationSize, int generations, int selectSize, int bestSize,
                                                   int selectStart, int selectEnd, int selectIncrement, int bestStart, int bestEnd,
                                                   int bestIncrement, int changeStart, int changeEnd, int changeIncrement, int thread, int threads)
{
    this->dir=QDir(dir);
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->selectSize=selectSize;
    this->bestSize=bestSize;
    this->selectStart=selectStart;
    this->selectEnd=selectEnd;
    this->selectIncrement=selectIncrement;
    this->bestStart=bestStart;
    this->bestEnd=bestEnd;
    this->bestIncrement=bestIncrement;
    this->bestIncrement=bestIncrement;
    this->changeStart=changeStart;
    this->changeEnd=changeEnd;
    this->changeIncrement=changeIncrement;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
}

void BeeColonyTestMultiThread::run()
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
        if(!fileFromDir.isDir())
        {
            count++;
            if(count % threads == thread)
            {
                for(int selectValue = selectStart; selectValue <= selectEnd; selectValue+=selectIncrement)
                {
                    for(int bestValue = bestStart; bestValue <= bestEnd; bestValue+=bestIncrement)
                    {
                        for(int changeValue = changeStart; changeValue <= changeEnd; changeValue+=changeIncrement)
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
                                emit wrongFile();
                                return;
                            }
                            population.setUpPopulation(seed, populationSize, &problem);
                            population.calculateFitnesses(&problem);
                            algorithm.setUpAlgorithm(generations, &problem, &population, selectSize, bestSize, selectValue, bestValue, changeValue);
                            int value;
                            if(thread == 0){
                                value = threads-1;
                            }else{
                                value = thread-1;
                            }
                            if(selectValue == selectStart && bestValue == bestStart && changeValue == changeStart)
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
                            if(count >= total && selectValue == selectEnd && bestValue == bestEnd && changeValue == changeEnd){
                                ended = 1;
                            }else{
                                ended = 0;
                            }
                            emit problemEnded(QString::number(selectValue) + ";" + QString::number(bestValue) + ";" + QString::number(changeValue) + ";" +
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
