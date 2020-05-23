#pragma once

#include "../TSP.h"
#include "../graph.h"

class BruteForce : public TSP
{
public:
    BruteForce();
    BruteForce(Graph &graph);
    BruteForce(Graph &&graph);

    void run();

    void initializePath(int *paths, int V);
    void permutation(int array[], int size, int n);
    void walkThePath(int *array);
};
