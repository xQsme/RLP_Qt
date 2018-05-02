#include "custommultithread.h"

CustomMultiThread::CustomMultiThread()
{

}

CustomMultiThread::CustomMultiThread(QDir dir, int populationSize, int generations, int elitism, int mutation, int thread, int threads)
{
    this->dir=dir;
    this->populationSize=populationSize;
    this->generations=generations;
    this->elitism=elitism;
    this->mutation=mutation;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
}

void CustomMultiThread::run()
{
    Problem problem;
    Population population;
    CustomAlgorithm algorithm;
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
                for(int seed = 5; seed <= 100; seed+=15)
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
                    algorithm.setUpAlgorithm(elitism, mutation, generations);
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
                    emit problemEnded(getFileInfo(fileFromDir.fileName()) + QString::number(seed) + ";" +
                                                      QString::number(bestGeneration) + ";" + QString::number(bestTime) + ";" +
                                                      QString::number(population.getBestIndividual().getFitness()) + ";" +
                                                      QString::number(population.getBestIndividual().getRegenerators()) + ";" +
                                                      QString::number(population.getBestIndividual().getDisconnected()), ended);
                }
            }
        }
    }
}

QString CustomMultiThread::getFileInfo(QString file)
{
    QString result;
    int reading=0;
    foreach(QChar c, file)
    {
        if (c.isDigit())
        {
            reading=1;
            result.append(c);
        }
        else
        {
            if(reading == 1)
            {
                result.append(";");
                reading=0;
            }
        }
    }
    QStringList list = result.split(";");
    if(list[0].toInt() < 100)
    {
        list[0] = "0" + list[0];
    }
    if(list[2].toInt() < 10)
    {
        list[2] = "0" + list[2];
    }
    result = list.join(";");
    return result;
}

