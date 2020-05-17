#include <algorithm>
#include <string.h>
#include <iostream>
#include <vector>

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

/**
 * Função principal do algoritmo do Caixeiro Viajante usando Força Bruta
 */
void DynamicProgramming::run()
{
    int V = this->graph.getV();

    this->distances = new double *[V];

    for (int i = 0; i < V; i++)
    {
        distances[i] = new double[V];
        for (int j = 0; j < V; j++)
        {
            this->distances[i][j] = UNDEFINED;
        }
    }

    cout << "minDistance: " << walkGraph() << endl;
    cout << "distance" << distance;

    for (int i = 0; i < V; i++) delete[] distances[i];
    delete[] distances;
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
