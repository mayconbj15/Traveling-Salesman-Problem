#pragma once

#include "../TSP.h"
#include "../graph.h"

class BruteForce : public TSP
{
public:
    BruteForce();
    BruteForce(Graph graph);
    
    void run();
    
    int *initializePath(int *paths, int V);
    void permutation(int array[], int size, int n);
    void walkThePath(int *array);
};
