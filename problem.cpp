#include "problem.h"

Problem::Problem()
{

}

void Problem::setUpProblem(QString filename){
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
    }

    int check = 0; //Verificar se tem pesos
    int done = 0; //Ja leu pesos todos
    int skipped = 0; //Ja passou a linha após ler os pesos
    int count = 0; //Linha do ficheiro
    int idx = 0; //Linha na matriz
    int maxConnections = 0;
    int currentConnections = 0;
    total = 0;
    connections = 0;
    weights.clear();
    nodes.clear();
    connectionsWeight.clear();

    QTextStream stream(&file);

    while (!stream.atEnd())
    {
       QString line = stream.readLine();
       count++;
       if (total == 0 || connections == 0 || check == 0)
       { //As 3 primeiras linhas
           if (connections != 0)
           { //Verificar se tem pesos
               check = 1;
               if (line.indexOf("Weight") != -1)
               {
                   hasWeight = 1;
               }
               else
               {
                   hasWeight = 0;
               }
           }
           else if (total != 0) { //Total de ligações
               if (line.indexOf("=") == -1)
               {
                    throw std::invalid_argument("wrong file!");
               }
               if (line.indexOf(";") == -1)
               {
                   connections = line.mid(line.indexOf("=") + 2).toInt();
               }
               else
               {
                   line = line.left(line.indexOf(";"));
                   connections = line.mid(line.indexOf("=") + 1).toInt();
               }
           }
           else
           { //Total de nós
               if (line.indexOf(";") == -1)
               {
                   if(line.indexOf("=")==-1){
                       throw std::invalid_argument("wrong file!");
                   }
                   total = line.mid(line.indexOf("=") + 2).toInt();
               }
               else
               {
                   if(line.indexOf("=")==-1){
                       throw std::invalid_argument("wrong file!");
                   }
                   line = line.left(line.indexOf(";"));
                   total = line.mid(line.indexOf("=")+1).toInt();
               }
               for (int index = 0; index < total; ++index)
               {
                   {
                       nodes << QVector<int>();
                   }
               }
           }
       }
       else
       {
           if (done == 1 && skipped == 0)
           { //ja leu pesos e ainda nao passou linha
               skipped = 1;
           }
           else
           { //Nao tem pesos ou ja passou linha
               if ((count > 4 && count % 2 != 0 && hasWeight == 0) || done == 1) { //Linhas impares para quando nao tem pesos, todas as linhas quando ja leu pesos
                   currentConnections=0;
                   QStringList list;
                   if(hasWeight==1)
                   {
                       list = line.split("\t\t");
                   }
                   else
                   {
                       list = line.split("  ");
                   }
                   foreach(QString value, list)
                   {
                       if (nodes[idx].length() == total)
                       {
                           break;
                       }
                       if(value.toInt() != 0)
                       {
                           nodes[idx] << 1;
                           currentConnections++;
                       }
                       else
                       {
                           nodes[idx] << 0;
                       }
                   }
                   connectionsWeight << --currentConnections;
                   if(maxConnections < currentConnections)
                   {
                       maxConnections = currentConnections;
                   }
                   if (++idx == total) {
                       break;
                   }
               }
               else if (hasWeight == 1) { //Ler os pesos
                   weights << line.toInt();
                   idx++;
                   if (idx == total) {
                       idx = 0;
                       done = 1;
                   }
               }
           }
       }
    }
    file.close();

    for(int i = 0; i < connectionsWeight.length(); i++){
        connectionsWeight[i] /= maxConnections;
    }
}

QVector<QVector<int>> Problem::getNodes()
{
    return nodes;
}

QVector<int> Problem::getWeights()
{
    return weights;
}

int Problem::hasWeights()
{
    return hasWeight;
}

int Problem::getTotal()
{
    return total;
}

int Problem::getConnections()
{
    return connections;
}

QVector<float> Problem::getConnectionsWeight(){
    return connectionsWeight;
}
