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

void Graph::createLigation(int x, int y, double weight)
{
    this->graph[x][y] = weight;
    this->graph[y][x] = weight;
}

int Graph::getV()
{
    return this->V;
}

double **Graph::getGraph()
{
    return this->graph;
}

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

void Graph::newRandomGraph()
{
    double number;

    srand(time(NULL));

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            createLigation(i, j, (double)(rand() % 10 + 1));
        }
    }
}