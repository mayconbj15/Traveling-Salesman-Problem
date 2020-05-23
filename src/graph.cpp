#include "graph.h"
#include "TSP.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define UNDEFINED -1

using namespace std;

Graph::Graph() {}

/**
 * Inicializa um novo grafo com V vértices
 *
 * @param V número de vértices do grafo
 */
Graph::Graph(int V)
{
    this->V = V;

    initializeGraph();
}

/**
 * Destrutor padrão da classe
 */
Graph::~Graph()
{
    for (int i = 0; i < this->V; i++)
        delete[] graph[i];
    delete[] graph;
}

/**
 * Construtor que recebe um grafo já construído
 */
Graph::Graph(const Graph &other)
{
    int numVertices = V = other.V;
    graph = new double *[numVertices];

    for (size_t i = 0; i < numVertices; i++)
    {
        graph[i] = new double[numVertices];
        memcpy(graph[i], other.graph[i], sizeof(double) * numVertices);
    }
}

/**
 * Inicializa um grafo com valores padrões igual a -1
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
 * Função que cria uma aresta bidirecional entre dois vertices com um determinado
 * peso
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
int Graph::getV() { return this->V; }

double **Graph::getGraph() { return this->graph; }

/**
 * Função para printar o grafo
 */
void Graph::print()
{
    cout << "GRAPH:" << endl;
    for (int i = 0; i < this->V; i++)
    {
        for (int j = 0; j < this->V; j++)
        {
            cout << (int)this->graph[i][j] << " ";
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
            if (i != j && j > i) createLigation(i, j, (double)(rand() % 10 + 1));
        }
    }
}

/**
 * Verifica se uma aresta que começa em x e termina em y já existe no Grafo
 */
bool Graph::edgeExist(int x, int y) { return graph[x][y] != UNDEFINED; }
