#pragma once

#include "../TSP.h"
#include "../graph.h"

class BranchAndBound : public TSP
{
public:
    BranchAndBound(Graph graph);
    
    void run();

    void atualizarMelhorCaminho(int* caminhoParcial);
    void branchAndBound(
        int parcial, int nivel, int *caminhoParcial, bool *visitados, int menorCaminho);
};