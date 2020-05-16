#pragma once

#include "../TSP.h"
#include "../graph.h"

class DynamicProgramming : public TSP
{
public:
    DynamicProgramming();
    DynamicProgramming(Graph graph);
    
    void run();
};
