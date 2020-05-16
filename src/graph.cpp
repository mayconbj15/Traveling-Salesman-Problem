#include "graph.h"
#include "TSP.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define UNDEFINED -1

using namespace std;

Graph::Graph() {}

Graph::Graph(int V)
{
    this->V = V;

    initializeGraph();
}

/**
 * Inicializa um grafo com valores default
 */
void Graph::initializeGraph()
{
    this->graph = new double *[V];

    for (int i = 0; i < this->V; i++)
    {
        graph[i] = new double[V];
        for (int j = 0; j < this->V; j++)
        {
            this->graph[i][j] = UNDEFINED;
        }
    }
}

/**
 * Função que cria uma aresta bidirecional entre dois vertices com um determinado peso
 * 
 * @param x vertice inicial
 * @param y vertice final
 * @param weight peso da aresta
 */
void Graph::createLigation(int x, int y, double weight)
{
    this->graph[x][y] = weight;
    this->graph[y][x] = weight;
}

/**
 * Função que retorna a quantidade de vertices do grafo
 * 
 * @return quantidade de vertices do grafo
 */
int Graph::getV()
{
    return this->V;
}

double **Graph::getGraph()
{
    return this->graph;
}

/**
 * Função para printar o grafo
 */
void Graph::print()
{
    for (int i = 0; i < this->V; i++)
    {
        for (int j = 0; j < this->V; j++)
        {
            cout << this->graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * Função para gerar um novo grafo com número aleatórios
 */
void Graph::newRandomGraph()
{
    double number;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i != j && j > i)
                createLigation(i, j, (double)(rand() % 10 + 1));
        }
    }
}