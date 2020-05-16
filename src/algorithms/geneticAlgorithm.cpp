#include <algorithm>

#include "../graph.h"
#include "geneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm() : TSP("Genetic Algorithm") {}
GeneticAlgorithm::GeneticAlgorithm(Graph graph) : TSP(graph, "Genetic Algorithm") {}

typedef struct {
    int *cities;
    int pathCost;
} Individual;

/**
 * @return Array with the sequence of cities. Ex.: { 0, 7, 5, 3, 0 }.
 */
int *createRandomPath(int numVertices)
{
    int city;
    int *cities = new int[numVertices + 1]();
    int *citiesEnd = cities + numVertices + 1 - 1;
    cities[0] = cities[numVertices] = 0;

    for (size_t i = 1; i < numVertices; i++)
    {
        do {
            city = rand() % (numVertices - 1) + 1;
        } while (find(cities + 1, citiesEnd, city) != citiesEnd);

        cities[i] = city;
    }

    return cities;
}

/**
 * Based on https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/
 */
void GeneticAlgorithm::run()
{
    int numVertices = this->graph.getV();
    // int populationSize = ((numVertices - 1) * (numVertices - 1)) / 4;
    // if (populationSize < 1) populationSize = 1;
    // int *bestIndividual = createRandomPath(numVertices), *individual;
    // int bestFitness = sumPath(bestIndividual), fitness;

    // delete bestIndividual;
}
