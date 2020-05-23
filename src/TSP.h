#pragma once

#include <memory>
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
    unique_ptr<int[]> cities;

    /** Nome do algoritmo */
    string name;
    /** Tempo gasto na última execução */
    double time;
    /** Tempo gasto acumulado */
    double totalTime = 0;

    virtual void run() = 0;

    double sumPath(int *array, int arraySize);
    double sumPath(int *array);
    void showResult();

public:
    TSP();
    TSP(string name);
    TSP(Graph &graph, string name);
    TSP(Graph &&graph, string name);

    void setGraph(Graph &graph);
    void setName(string name);
    string getName();
    void setTotalTime(double totalTime);
    double getTotalTime();
    void printClock();
    double runAndCountTime();

    void printPath(int *array, int n);
};
