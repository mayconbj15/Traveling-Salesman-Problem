#include <algorithm>
#include <string.h>

#include "../graph.h"
#include "../constants.h"
#include "dynamicProgramming.h"

using namespace std;

DynamicProgramming::DynamicProgramming() : TSP("Dynamic Programming") {}
DynamicProgramming::DynamicProgramming(Graph graph) : TSP(graph, "Dynamic Programming") {}

void DynamicProgramming::run()
{
    //
}
