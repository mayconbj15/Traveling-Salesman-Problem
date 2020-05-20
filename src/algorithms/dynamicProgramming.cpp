#include <algorithm>
#include <string.h>
#include <iostream>
#include <vector>
#include <bitset>

#include "../graph.h"
#include "../constants.h"
#include "dynamicProgramming.h"

using namespace std;

DynamicProgramming::DynamicProgramming() : TSP("Dynamic Programming") {}
DynamicProgramming::DynamicProgramming(Graph &graph) : TSP(graph, "Dynamic Programming") {}
DynamicProgramming::DynamicProgramming(Graph &&graph) : TSP(graph, "Dynamic Programming") {}

/**
 * Função que gera um conjunto de vértices padrão que será permutado
 * 
 * @return um array com de 0 a V
 */
int *DynamicProgramming::initializePath(int *paths, int V)
{
    int i = 0;
    for (i = 0; i < V; i++)
        paths[i] = i;
    paths[i] = 0;

    return paths;
}

/**
 * Função que percorre um determinado conjunto de vertices dado em um array de inteiro
 * e faz a soma de seus pesos
 * 
 * @param array array de inteiro com os vértices a serem visitados
 */
void DynamicProgramming::walkThePath(int *array)
{
    int V = this->graph.getV();
    double sum = sumPath(array);

    if (sum == -1)
        return;
    if (sum < this->distance)
    {
        this->distance = sum;

        //preenche o vetor de cidades com o maior caminho
        for (int i = 0; i < V; i++)
            this->cities[i] = array[i];
    }
}

/**
 * Função que recebe um array de inteiros e gera suas permutações
 *  do elemento 1 ao n-1, mantendo o primeiro elemento fixo
 * 
 * @param array array de inteiro a serem permutados
 * @param size tamanho lógico do vetor de array atual
 * @param n tamanho real do vetor
 * 
 */
void DynamicProgramming::permutation(int array[], int size, int n)
{
    if (size == 1) //final da permutação
    {
        printArray(array, n);
        //walkThePath(array);
    }

    for (int i = 1; i < size; i++)
    {
        permutation(array, size - 1, n);

        if (size % 2 == 1)
            swap(array[1], array[size - 1]);
        else
            swap(array[i], array[size - 1]);
    }
}

bool notIn(int subset, int city) { return ((1 << city) & subset) == 0; }

int removeCity(int city, int subset) { return subset ^ (1 << city); }

/**
 * Given an ending city and a set of cities that need to be visited to reach this
 * city, returns the minimum cost to reach it passing through all cities in the set.
 * 
 * @param memoTable Table were the rows are acessed via an integer number that
 * represents the subset of cities (Ex.: 1110 = 14 would represent a set with cities
 * 1, 2 and 3 considering that the first city is 0) and the columns are also acessed
 * via an integer number that represents the desired ending city. So,
 * memoTable[14][0] will represent the minimum cost to reach city 0 passing through
 * the cities in the subset {1, 2, 3}.
 * @param graph Hamiltonian graph.
 * @param citiesSubset The subset of cities this function will analyze.
 * @param endingCity A city in the subset that will be the last in the path.
 * @param numCities Total number of cities.
 * 
 * @return The minimum cost to reach the endingCity passing through all cities in
 * the citiesSubset.
 */
int dynamicTSP(
    vector<vector<int>> &memoTable,
    double **graph,
    int citiesSubset,
    int endingCity,
    int numCities
)
{
    int newSubset = removeCity(endingCity, citiesSubset);
    int bestCost = MAX, cost = memoTable[newSubset][endingCity];
    // cout << "############################" << endl;
    // cout << "oldpath: " << bitset<8 * sizeof(citiesSubset)>(citiesSubset)
    //     << endl << "   path: " << bitset<8 * sizeof(newSubset)>(newSubset)
    //     << endl;

    if (cost != UNDEFINED) return cost;
    
    for (int newEndingCity = 1; newEndingCity < numCities; newEndingCity++)
    {
        if (notIn(newSubset, newEndingCity)) continue;

        cost = dynamicTSP(memoTable, graph, newSubset, newEndingCity, numCities)
            + graph[newEndingCity][endingCity];

        if (cost < bestCost) bestCost = cost;
    }
    
    return memoTable[newSubset][endingCity] = bestCost;
}

void getSolution(
    vector<vector<int>> &memoTable,
    int citiesSubset,
    int endingCity,
    int numCities,
    int *cities
)
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
    cities[n++] = endingCity;
}

void initMemoTable(vector<vector<int>> &memoTable, double **graph, int numCities)
{
    for (size_t city = 1; city < numCities; city++)
        memoTable[0][city] = graph[city][0];
}

int dynamicTSP(double **graph, int numCities, int *cities)
{
    // 1 << numCities = 2^numCities
    vector<vector<int>> memoTable(1 << numCities, vector<int>(numCities, UNDEFINED));
    initMemoTable(memoTable, graph, numCities);

    // if we have 3 cities, citiesSubset will receive 111
    int citiesSubset = (1 << numCities) - 1;
    const int endingCity = 0;

    int cost = dynamicTSP(memoTable, graph, citiesSubset, endingCity, numCities);
    getSolution(memoTable, citiesSubset, endingCity, numCities, cities);
    return cost;
}

/**
 * Função principal do algoritmo do Caixeiro Viajante usando Força Bruta
 */
void DynamicProgramming::run()
{
    distance = dynamicTSP(graph.getGraph(), graph.getV(), cities);
    // int V = this->graph.getV();

    // this->distances = new double *[V];

    // for (int i = 0; i < V; i++)
    // {
    //     distances[i] = new double[V];
    //     for (int j = 0; j < V; j++)
    //     {
    //         this->distances[i][j] = UNDEFINED;
    //     }
    // }

    // cout << "minDistance: " << walkGraph() << endl;
    // cout << "distance" << distance;

    // for (int i = 0; i < V; i++) delete[] distances[i];
    // delete[] distances;
}

/* double DynamicProgrammin::cost(int *array, int n)
{
    double sum = costRec(array, 0, (n + 1), 0);
}

double DynamicProgramming::costRec(int *array, int i, int n, double sum)
{
    if (n == 2)
    {
        sum = graph.getGraph()[i][n];
    }
    else
    {
        sum = min(graph.getGraph()[i][n] + cost(array, i, n - 1, sum));
    }

    return cost;
} */

bool DynamicProgramming::allVertexVisited(vector<bool> visited)
{
    bool allVisited = true;

    for (int i = 0; i < graph.getV() && allVisited; i++)
    {
        if (!visited[i])
            allVisited = false;
    }

    return allVisited;
}

double DynamicProgramming::walkGraph()
{
    /*    int V = graph.getV();
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    } */

    vector<bool> visited(graph.getV());

    return walkGraphRec(0, 0, 0.0, visited);
}

double DynamicProgramming::walkGraphRec(int src, int i, double sum, vector<bool> visited)
{
    visited[src] = true;
    if (allVertexVisited(visited) && graph.getGraph()[src][0] != UNDEFINED)
    {
        int actualDistance = graph.getGraph()[src][0];
        distances[src][0] = actualDistance;

        return actualDistance;
    }

    int minDistance = MAX;

    for (int i = 0; i < graph.getV(); i++)
    {
        /*  if (allVertexVisited(visited) && graph.getGraph()[src][0] != UNDEFINED)
        {
            int actualSum = graph.getGraph()[src][0];
            if (actualSum < this->distance)
            {
                cout << "PATH: " << src << " ";
                this->distance = actualSum;
                return actualSum;
            }
        } */
        if (graph.getGraph()[src][i] != UNDEFINED && !visited[i])
        {
            /*  if (distances[src][i] != UNDEFINED)
                return distances[src][i]; */

            cout << "PATH: " << src << " ";
            distances[src][i] = graph.getGraph()[src][i];
            sum = walkGraphRec(i, src, sum, visited);
            sum += distances[src][i];

            if (sum < minDistance)
            {
                minDistance = sum;
            }
            /*   if (sum < minDistance)
            {
                sum += graph.getGraph()[src][i];
                minDistance = sum;
                this->distance = minDistance;
            } */

            /*  if (sum < this->distance)
                this->distance = sum; */
        }
    }
    cout << endl;
    return minDistance;
}
