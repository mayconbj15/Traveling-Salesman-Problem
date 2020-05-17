#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>

#include <string.h>

#include "../graph.h"
#include "../constants.h"
#include "geneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm() : TSP("Genetic Algorithm") {}
GeneticAlgorithm::GeneticAlgorithm(Graph &graph) : TSP(graph, "Genetic Algorithm") {}
GeneticAlgorithm::GeneticAlgorithm(Graph &&graph) : TSP(graph, "Genetic Algorithm") {}

/**
 * The returned array need to be deleted.
 * 
 * @return Array with the sequence of cities. Ex.: { 0, 7, 5, 3, 0 }.
 */
int *GeneticAlgorithm::createRandomPath(int numVertices)
{
    int city;
    int *cities = new int[numVertices + 1]();
    int *citiesEnd = cities + 1;
    cities[0] = cities[numVertices] = 0;

    for (size_t i = 1; i < numVertices; i++, citiesEnd++)
    {
        do {
            city = rand() % (numVertices - 1) + 1;
        } while (
            !graph.edgeExist(cities[i - 1], city) || // The edge need to exist
            // And the city can't already exist in the path
            find(cities + 1, citiesEnd, city) != citiesEnd
        );

        cities[i] = city;
    }

    return cities;
}

bool pathsAreEqual(int *path0, int *path1, int pathSize)
{
    bool areEqual = true;

    for (size_t i = 0; i < pathSize && areEqual; i++)
        areEqual = path0[i] == path1[i];

    return areEqual;
}

void GeneticAlgorithm::mutateIndividual(
    Individual &individual, int numVertices, int numOfTries = 3)
{
    if (numOfTries > 0)
    {
        int *newPath = new int[numVertices + 1];
        memcpy(newPath, individual.cities, sizeof(int) * (numVertices + 1));
        int mutationIndex0 = 1 + rand() % (numVertices - 1);
        int mutationIndex1 = 1 + rand() % (numVertices - 1);

        while (mutationIndex0 == mutationIndex1)
            mutationIndex1 = 1 + rand() % (numVertices - 1);
        
        int aux = newPath[mutationIndex0];
        newPath[mutationIndex0] = newPath[mutationIndex1];
        newPath[mutationIndex1] = aux;

        int newPathCost = sumPath(newPath);
        if (newPathCost == -1 || newPathCost >= individual.pathCost)
        {
            delete[] newPath;
            mutateIndividual(individual, numVertices, numOfTries - 1);
        }
        
        else
        {
            delete[] individual.cities;
            individual.cities = newPath;
            individual.pathCost = newPathCost;
        }
    }
}

bool GeneticAlgorithm::mutatePopulation(
    vector<Individual> &population,
    int mutationRate,
    int numVertices,
    Individual &bestPath
)
{
    for (auto &&individual : population)
        if (rand() % 100 < mutationRate)
        {
            mutateIndividual(individual, numVertices);

            if (individual.pathCost < bestPath.pathCost)
            {
                bestPath.pathCost = individual.pathCost;
                bestPath.cities = individual.cities;
            }
        }
}

void GeneticAlgorithm::createRandomPopulation(
    vector<Individual> &population,
    int populationSize,
    int numVertices,
    Individual &bestPath
)
{
    vector<Individual>::iterator individualPtr;

    for (size_t i = 0; i < populationSize; i++)
    {
        Individual &individual = population[i];
        do {
            individual.cities = createRandomPath(numVertices);

            // Check if createRandomPath has generated a path that already exists
            // in the population
            individualPtr = find_if(population.begin(), population.begin() + i,
                [&individual, numVertices](Individual& currentIndividual){
                    return pathsAreEqual(
                        individual.cities,
                        currentIndividual.cities,
                        numVertices
                    );
                }
            );

            if (individualPtr == population.begin() + i) break;
            else delete[] individual.cities;
        } while (true);

        individual.pathCost = sumPath(individual.cities);

        if (individual.pathCost < bestPath.pathCost)
        {
            bestPath.pathCost = individual.pathCost;
            bestPath.cities = individual.cities;
        }
    }
}

/**
 * Based on https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/
 */
void GeneticAlgorithm::run()
{
    int numVertices = this->graph.getV();
    int numGenerations = numVertices * numVertices;
    int populationSize = numGenerations / 4;
    if (populationSize < 1) populationSize = 1;
    int mutationRate = 50;

    Individual bestPath;
    bestPath.pathCost = MAX;
    vector<Individual> population(populationSize);
    createRandomPopulation(population, populationSize, numVertices, bestPath);

    for (int generationNum = 1; generationNum <= numGenerations; generationNum++)
        mutatePopulation(population, mutationRate, numVertices, bestPath);

    // for (auto &&individual : population) delete[] individual.cities;
    cities = bestPath.cities;
    distance = bestPath.pathCost;
}
