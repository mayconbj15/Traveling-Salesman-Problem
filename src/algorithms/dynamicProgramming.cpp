#include "dynamicProgramming.h"

#include <string.h>

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

#include "../constants.h"
#include "../graph.h"

using namespace std;

DynamicProgramming::DynamicProgramming() : TSP("Dynamic Programming") {}
DynamicProgramming::DynamicProgramming(Graph &graph)
    : TSP(graph, "Dynamic Programming")
{
}
DynamicProgramming::DynamicProgramming(Graph &&graph)
    : TSP(graph, "Dynamic Programming")
{
}

void getSolution(vector<vector<int>> &memoTable, int citiesSubset, int endingCity,
                 int numCities, int *cities);

/**
 * @brief Checa se uma cidade não está no subconjunto.
 *
 * @param city Índice da cidade a ser checada. Considerando que a city 0 seria a
 * última à direita (Little Endian).
 * @param subset Subconjunto de cidades. Ex.: subset = 14 = 1110 (cidades 1, 2 e 3)
 *
 * @return true caso a cidade não esteja no subconjunto. Ex.: notIn(14, 0) = true.
 * @return false caso contrário.
 */
bool notIn(int subset, int city) { return ((1 << city) & subset) == 0; }

/**
 * @brief Remove uma cidade do subconjunto de cidades. Um subconjunto é uma sequência
 * de bits.
 *
 * @param city Índice da cidade a ser removida. Considerando que a city 0 seria a
 * última à direita (Little Endian).
 * @param subset Subconjunto de cidades. Ex.: subset = 14 = 1110 (cidades 1, 2 e 3)
 *
 * @return int O novo subconjunto com a cidade removida.
 * Ex.: removeCity(2, 14) = 10 = 1010
 */
int removeCity(int city, int subset) { return subset ^ (1 << city); }

/**
 * Given a set of cities and an ending city in this set, returns the
 * minimum cost to reach it passing through all cities in the set.
 *
 * @param memoTable Table were the rows are acessed via an integer number that
 * represents the subset of cities (Ex.: 1110 = 14 would represent a set with
 * cities 1, 2 and 3. Each 1 represent a city in the set) and the columns are
 * also acessed via an integer number that represents the desired ending city.
 * So, memoTable[14][0] will represent the minimum cost to reach city 0 passing
 * through the cities in the subset {1, 2, 3}.
 * @param graph Hamiltonian graph.
 * @param citiesSubset The subset of cities this function will analyze.
 * @param endingCity A city in the subset that will be the last in the path.
 * @param numCities Total number of cities.
 *
 * @return The minimum cost to reach the endingCity passing through all cities
 * in the citiesSubset.
 */
int dynamicTSP(vector<vector<int>> &memoTable, double **graph, int citiesSubset,
               int endingCity, int numCities)
{
    int newSubset = removeCity(endingCity, citiesSubset);
    int bestCost = MAX, cost = memoTable[newSubset][endingCity];

    if (cost != UNDEFINED) return cost;

    for (int newEndingCity = 1; newEndingCity < numCities; newEndingCity++)
    {
        if (notIn(newSubset, newEndingCity)) continue;

        cost = dynamicTSP(memoTable, graph, newSubset, newEndingCity, numCities) +
               graph[newEndingCity][endingCity];

        if (cost < bestCost) bestCost = cost;
    }

    return memoTable[newSubset][endingCity] = bestCost;
}

/**
 * @brief Populate memoTable with know values from the graph. For example, for the
 * empty cities subset (0), if I consider the ending city as 1, then, the cost to
 * pass through this path is the cost to go from city 1 to city 0 that is the
 * starting and ending city.
 *
 * @param memoTable Table were the rows are acessed via an integer number that
 * represents the subset of cities (Ex.: 1110 = 14 would represent a set with
 * cities 1, 2 and 3. Each 1 represent a city in the set) and the columns are
 * also acessed via an integer number that represents the desired ending city.
 * So, memoTable[14][0] will represent the minimum cost to reach city 0 passing
 * through the cities in the subset {1, 2, 3}.
 * @param graph Hamiltonian graph.
 * @param numCities Total number of cities.
 */
void initMemoTable(vector<vector<int>> &memoTable, double **graph, int numCities)
{
    for (size_t city = 1; city < numCities; city++)
        memoTable[0][city] = graph[city][0];
}

/**
 * @brief Solve the Travelling Salesman Problem using Dynamic Programming.
 *
 * @param graph Given graph.
 * @param numCities Number of cities (number of vertices of the graph).
 * @param cities Pointer to an array to store the sequence of cities of the best
 * solution.
 *
 * @return int The cost of the best solution.
 */
int dynamicTSP(double **graph, int numCities, int *cities)
{
    // 1 << numCities = 2^numCities
    /** See dynamicTSP() documentation above to understand this table */
    vector<vector<int>> memoTable(1 << numCities, vector<int>(numCities, UNDEFINED));
    initMemoTable(memoTable, graph, numCities);

    // if we have 3 cities, citiesSubset will receive 111
    int citiesSubset = (1 << numCities) - 1, endingCity = 0;

    int cost = dynamicTSP(memoTable, graph, citiesSubset, endingCity, numCities);
    getSolution(memoTable, citiesSubset, endingCity, numCities, cities);
    return cost;
}

void DynamicProgramming::run()
{
    distance = dynamicTSP(graph.getGraph(), graph.getV(), cities.get());
}

/**
 * @brief Discover what is the best solution Dynamic Programming found.
 *
 * @param memoTable Table were the rows are acessed via an integer number that
 * represents the subset of cities (Ex.: 1110 = 14 would represent a set with
 * cities 1, 2 and 3. Each 1 represent a city in the set) and the columns are
 * also acessed via an integer number that represents the desired ending city.
 * So, memoTable[14][0] will represent the minimum cost to reach city 0 passing
 * through the cities in the subset {1, 2, 3}.
 * @param citiesSubset The subset of cities this function will analyze.
 * @param endingCity A city in the subset that will be the last in the path.
 * @param numCities Total number of cities.
 * @param cities Pointer to an array to store the sequence of cities of the best
 * solution.
 */
void getSolution( // Down the tree getting the best path after dynamic
                  // programming
    vector<vector<int>> &memoTable, int citiesSubset, int endingCity, int numCities,
    int *cities)
{
    int cost, bestCost = MAX, subset, bestSubset, bestCity, n = 0;
    int newSubset = removeCity(endingCity, citiesSubset);
    cities[n++] = endingCity;

    for (size_t i = 1; i < numCities; i++)
    {
        bestCost = MAX;
        for (int city = 1; city < numCities; city++)
        {
            if (notIn(newSubset, city)) continue;

            subset = removeCity(city, newSubset);
            cost = memoTable[subset][city];

            if (cost < bestCost)
            {
                bestCost = cost;
                bestSubset = subset;
                bestCity = city;
            }
        }
        newSubset = bestSubset;
        cities[n++] = bestCity;
    }
}
