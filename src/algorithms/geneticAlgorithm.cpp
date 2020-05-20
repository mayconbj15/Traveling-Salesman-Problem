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

void createMutationIndexes(int &mutationIndex0, int &mutationIndex1, int numVertices)
{
    mutationIndex0 = 1 + rand() % (numVertices - 1);
    mutationIndex1 = 1 + rand() % (numVertices - 1);
    while (mutationIndex0 == mutationIndex1)
        mutationIndex1 = 1 + rand() % (numVertices - 1);
}

void mutate(int *newPath, int mutationIndex0, int mutationIndex1)
{
    int aux = newPath[mutationIndex0];
    newPath[mutationIndex0] = newPath[mutationIndex1];
    newPath[mutationIndex1] = aux;
}

void GeneticAlgorithm::mutateIndividual(
    Individual &individual, int numVertices, int numOfTries = 3)
{
    if (numOfTries > 0)
    {
        int newPath[numVertices + 1];
        copy(individual.cities.begin(), individual.cities.end(), newPath);

        int mutationIndex0, mutationIndex1;
        createMutationIndexes(mutationIndex0, mutationIndex1, numVertices);
        mutate(newPath, mutationIndex0, mutationIndex1);

        int newPathCost = sumPath(newPath);
        if (newPathCost == -1 || newPathCost >= individual.pathCost)
            mutateIndividual(individual, numVertices, numOfTries - 1);
        else
        {
            copy(newPath, newPath + numVertices + 1, individual.cities.begin());
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

void GeneticAlgorithm::createRandomPath(int numVertices, vector<int> &cities)
{
    int city;
    auto citiesEnd = cities.begin() + 1;
    cities[0] = cities[numVertices] = 0;

    for (size_t i = 1; i < numVertices; i++, citiesEnd++)
    {
        do {
            city = rand() % (numVertices - 1) + 1;
        } while (
            !graph.edgeExist(cities[i - 1], city) || // The edge need to exist
            // And the city can't already exist in the path
            find(cities.begin() + 1, citiesEnd, city) != citiesEnd
        );

        cities[i] = city;
    }
}

bool pathsAreEqual(vector<int> &path0, vector<int> &path1, int pathSize)
{
    return memcmp(path0.data(), path1.data(), sizeof(int) * pathSize) == 0;
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
            createRandomPath(numVertices, individual.cities);

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
        } while (true);

        individual.pathCost = sumPath(individual.cities.data());

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

    Individual bestPath(numVertices + 1);
    bestPath.pathCost = MAX;
    vector<Individual> population(populationSize, Individual(numVertices + 1));
    createRandomPopulation(population, populationSize, numVertices, bestPath);

    for (int generationNum = 1; generationNum <= numGenerations; generationNum++)
        mutatePopulation(population, mutationRate, numVertices, bestPath);

    copy(bestPath.cities.begin(), bestPath.cities.end() - 1, cities.get());
    distance = bestPath.pathCost;
}
