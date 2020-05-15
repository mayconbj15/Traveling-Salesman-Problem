#pragma once

#include <string>

#include "graph.h"

using namespace std;

/**
 * Travelling Salesman Problem implementations:
 * - Brute force
 * - Branch and bound
 * - Dynamic programming
 * - Genetic algorithm
 */
class TSP
{
protected:
    Graph graph;

    double distance;
    int *cities;

    /** Nome do algoritmo */
    string name;
    /** Tempo gasto na última execução */
    double time;
    /** Média das execuções */
    double totalTime = 0;

    virtual void run() = 0;

    double sumPath(int *array, int arraySize);
    double sumPath(int *array);
    void showResult();

public:
    TSP(Graph graph, string name);

    void printClock();
    double runAndCountTime();
};
