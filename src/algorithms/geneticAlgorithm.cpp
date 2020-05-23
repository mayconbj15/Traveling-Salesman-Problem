#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include <string.h>

#include "../constants.h"
#include "../graph.h"
#include "geneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm() : TSP("Genetic Algorithm") {}
GeneticAlgorithm::GeneticAlgorithm(Graph &graph) : TSP(graph, "Genetic Algorithm") {}
GeneticAlgorithm::GeneticAlgorithm(Graph &&graph) : TSP(graph, "Genetic Algorithm")
{
}

/**
 * @brief Cria os índices onde o indivíduo será mutado.
 *
 * @param mutationIndex0 Referência para a variável que guardará o primeiro índice.
 * @param mutationIndex1 Referência para a variável que guardará o segundo índice.
 * @param numVertices Número de vértices do grafo.
 */
void createMutationIndexes(int &mutationIndex0, int &mutationIndex1, int numVertices)
{
    mutationIndex0 = 1 + rand() % (numVertices - 1);
    mutationIndex1 = 1 + rand() % (numVertices - 1);
    while (mutationIndex0 == mutationIndex1)
        mutationIndex1 = 1 + rand() % (numVertices - 1);
}

/**
 * @brief Muta um indivíduo trocando dois vértices de lugar.
 *
 * @param newPath Ponteiro para o novo caminho desse indivíduo.
 * @param mutationIndex0 Índice do primeiro vértice a ser trocado de lugar.
 * @param mutationIndex1 Índice do segundo vértice a ser trocado de lugar.
 */
void mutate(int *newPath, int mutationIndex0, int mutationIndex1)
{
    int aux = newPath[mutationIndex0];
    newPath[mutationIndex0] = newPath[mutationIndex1];
    newPath[mutationIndex1] = aux;
}

/**
 * @brief Tenta mutar um indivíduo algumas vezes para que ele se torne melhor.
 *
 * @param individual Indivíduo a ser mutado.
 * @param numVertices Número de vértices do grafo.
 * @param numOfTries Número de tentativas.
 */
void GeneticAlgorithm::mutateIndividual(Individual &individual, int numVertices,
                                        int numOfTries = 3)
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

/**
 * @brief Faz as mutações em toda a população baseando-se na taxa de mutação.
 *
 * @param population População do algoritmo.
 * @param mutationRate Taxa de mutação.
 * @param numVertices Número de vértices do grafo.
 * @param bestPath Ao mutar a população, esse indivíduo se transformará no novo
 * melhor indivíduo dela.
 */
void GeneticAlgorithm::mutatePopulation(vector<Individual> &population,
                                        int mutationRate, int numVertices,
                                        Individual &bestPath)
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

/**
 * @brief Cria um caminho hamiltoniano aleatório.
 *
 * @param numVertices Número de vértices do grafo.
 * @param cities Vetor que receberá esse caminho.
 */
void GeneticAlgorithm::createRandomPath(int numVertices, vector<int> &cities)
{
    int city;
    auto citiesEnd = cities.begin() + 1;
    cities[0] = cities[numVertices] = 0;

    for (size_t i = 1; i < numVertices; i++, citiesEnd++)
    {
        do
        {
            city = rand() % (numVertices - 1) + 1;
        } while ( // The edge need to exist
            !graph.edgeExist(cities[i - 1], city) ||
            // And the city can't already exist in the path
            find(cities.begin() + 1, citiesEnd, city) != citiesEnd);

        cities[i] = city;
    }
}

/**
 * @brief Cria um caminho para um indivíduo e checa se já existe outro indivíduo
 * com o mesmo caminho.
 *
 * @param numVertices Número de vértices do grafo.
 * @param i Variável de controle do loop externo. Representa também o número de
 * indivíduos gerados com sucesso - 1.
 * @param individual Indivíduo que receberá o novo caminho.
 * @param population População do algoritmo.
 *
 * @return true caso o indivíduo é válido, ou seja, não existe outro com o mesmo
 * caminho.
 * @return false caso contrário.
 */
bool GeneticAlgorithm::createIndividual(int numVertices, int i,
                                        Individual &individual,
                                        vector<Individual> &population)
{
    createRandomPath(numVertices, individual.cities);

    auto searchEnd = population.begin() + i;
    // Check if createRandomPath has generated a path that already exists
    // in the population
    auto individualPtr =
        find_if(population.begin(), searchEnd,
                [&individual, numVertices](Individual &currentIndividual) {
                    return equal(individual.cities.begin(), individual.cities.end(),
                                 currentIndividual.cities.begin());
                });

    return individualPtr == searchEnd;
}

/**
 * @brief Gera uma população inicial para o algoritmo genético. Cada indivíduo
 * será uma tupla (caminho, custoDoCaminho) onde 'caminho' é um vetor com os
 * índices dos vértices do caminho hamiltoniano e o 'custoDoCaminho' é
 * autoexplicativo.
 *
 * @param population Vetor que receberá a população.
 * @param populationSize Tamanho da população.
 * @param numVertices Número de vértices que o grafo tem.
 * @param bestPath Ao gerar a população, esse parâmetro será populado com o melhor
 * indivíduo até o momento.
 */
void GeneticAlgorithm::createRandomPopulation(vector<Individual> &population,
                                              int populationSize, int numVertices,
                                              Individual &bestPath)
{
    vector<Individual>::iterator individualPtr;

    for (size_t i = 0; i < populationSize; i++)
    {
        Individual &individual = population[i];
        // clang-format off
        while (!createIndividual(numVertices, i, individual, population));
        // clang-format on

        individual.pathCost = sumPath(individual.cities.data());

        if (individual.pathCost < bestPath.pathCost)
        {
            bestPath.pathCost = individual.pathCost;
            bestPath.cities = individual.cities;
        }
    }
}

/**
 * @brief Define o número de gerações, o tamanho da população e a taxa de mutação
 * para o algoritmo genético. Depois, cria a população de forma aleatória
 * e começa a realizar mutações para cada geração.
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
