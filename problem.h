#ifndef PROBLEM_H
#define PROBLEM_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>

class Problem
{
public:
    Problem();
    void libertarMemoria();
    void setUpProblem(QString filename);
    QVector<QVector<int>> getNodes();
    QVector<int> getWeights();
    int hasWeights();
    int getTotal();
    int getConnections();
private:
    QVector<QVector<int>> nodes;
    QVector<int> weights;
    int hasWeight = 0;
    int total=0;
    int connections = 0;
};

#endif // PROBLEM_H
