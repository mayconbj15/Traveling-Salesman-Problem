#pragma once

#include <vector>

#include "../TSP.h"
#include "../graph.h"

/**
 * Chromosome
 */
class Individual
{
public:
    /** Genes */
    vector<int> cities;
    int pathCost = -1;

    Individual(int numCities) { cities.resize(numCities); }
};

class GeneticAlgorithm : public TSP
{
public:
    GeneticAlgorithm();
    GeneticAlgorithm(Graph &graph);
    GeneticAlgorithm(Graph &&graph);

    void run();

    void createRandomPath(int numVertices, vector<int> &cities);

    void mutateIndividual(Individual &individual, int numVertices, int numOfTries);

    bool mutatePopulation(vector<Individual> &population, int mutationRate,
                          int numVertices, Individual &bestPath);

    void createRandomPopulation(vector<Individual> &population, int populationSize,
                                int numVertices, Individual &bestPath);
};
