#pragma once

#include "../TSP.h"
#include "../graph.h"

class GeneticAlgorithm : public TSP
{
public:
    GeneticAlgorithm(Graph graph);
    
    void run();
};