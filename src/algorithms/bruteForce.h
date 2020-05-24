#pragma once

#include "../TSP.h"
#include "../graph.h"

/**
 * Classe que implementa o paradigma de Força Bruta para resolver o problema do
 * Caixeiro Viajante
 */
class BruteForce : public TSP
{
public:
    BruteForce();
    BruteForce(Graph &graph);
    BruteForce(Graph &&graph);

    void run();

    void initializePath(int *paths, int V);
    void permutation(int array[], int size);
    void walkThePath(int *array);
};
