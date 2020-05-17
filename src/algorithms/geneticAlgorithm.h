#pragma once

#include "../TSP.h"
#include "../graph.h"

/**
 * Chromosome
 */
typedef struct {
    /** Genes */
    int *cities;
    int pathCost = -1;
} Individual;

class GeneticAlgorithm : public TSP
{
public:
    GeneticAlgorithm();
    GeneticAlgorithm(Graph &graph);
    GeneticAlgorithm(Graph &&graph);
    
    void run();

    int *createRandomPath(int numVertices);

    void mutateIndividual(Individual &individual, int numVertices, int numOfTries);

    bool mutatePopulation(
        vector<Individual> &population,
        int mutationRate,
        int numVertices,
        Individual &bestPath
    );

    void createRandomPopulation(
        vector<Individual> &population,
        int populationSize,
        int numVertices,
        Individual &bestPath
    );
};
