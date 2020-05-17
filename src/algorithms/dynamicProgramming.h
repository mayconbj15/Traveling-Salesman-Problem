#pragma once

#include "../TSP.h"
#include "../graph.h"

class DynamicProgramming : public TSP
{
public:
    DynamicProgramming();
    DynamicProgramming(Graph &graph);
    DynamicProgramming(Graph &&graph);

    double **distances;

    void run();

    int *initializePath(int *paths, int V);
    void permutation(int array[], int size, int n);
    void walkThePath(int *array);

    double cost(int i, int j, int n, double cost);
    double walkGraph();
    double walkGraphRec(int src, int i, double sum, vector<bool> visited);
    bool allVertexVisited(vector<bool> visited);
};
