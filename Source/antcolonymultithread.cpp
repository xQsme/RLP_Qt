#include "antcolonymultithread.h"

AntColonyMultiThread::AntColonyMultiThread()
{

}


AntColonyMultiThread::AntColonyMultiThread(QString dir, int seed, int populationSize, int generations, int probability_q,
                                           int q, int number_mods, int evaporation, int influence, int thread, int threads)
{
    this->dir=QDir(dir);
    this->seed=seed;
    this->populationSize=populationSize;
    this->generations=generations;
    this->probability_q=probability_q/100.0;
    this->q=q;
    this->number_mods=number_mods;
    this->evaporation=evaporation/100.0;
    this->influence=influence/100.0;
    this->thread=thread == threads - 1 ? 0 : thread+1;
    this->threads=threads;
}

void AntColonyMultiThread::run()
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
        if(!fileFromDir.isDir())
        {
            count++;
            if(count % threads == thread)
            {
                for(int s = seed; s <= seed+18; s+=2)
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
                    population.setUpPopulation(s, populationSize, &problem);
                    algorithm.setUpAlgorithm(generations, probability_q, q, number_mods, &population, &problem, evaporation, influence);
                    int value;
                    if(thread == 0){
                        value = threads-1;
                    }else{
                        value = thread-1;
                    }
                    if(s == seed)
                    {
                        emit newProblem(value, fileFromDir.fileName(), 100*count/total);
                    }
                    while(algorithm.generateNewPopulation(&population, &problem) == 1)
                    {
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
                    if(count >= total && s == seed+18){
                        ended = 1;
                    }else{
                        ended = 0;
                    }
                    emit problemEnded(getFileInfo(fileFromDir.fileName()) + getSeedString(s) +
                                                      QString::number(bestGeneration) + ";" + QString::number(bestTime) + ";" +
                                                      QString::number(population.getBestIndividual().getFitness()) + ";" +
                                                      QString::number(population.getBestIndividual().getRegenerators()) + ";" +
                                                      QString::number(population.getBestIndividual().getDisconnected()), ended);
                }
            }
        }
    }
}

QString AntColonyMultiThread::getFileInfo(QString file)
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

QString AntColonyMultiThread::getSeedString(int seed)
{
    QString result;
    if(seed < 100){
        result += "0";
    }
    if(seed < 10){
        result += "0";
    }
    result += QString::number(seed) + ";";
    return result;
}
