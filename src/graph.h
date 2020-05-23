#pragma once

#include <string.h>

class Graph
{
private:
    double **graph;
    int V;

    void initializeGraph();
    void printRoutes();

    /* Funções dos paradigmas */
    void permutation(int array[], int size, int n, double sum);
    void walkThePath(int *array);

public:
    Graph();
    Graph(int V);

    ~Graph();

    Graph(const Graph &other);

    Graph &operator=(const Graph &other)
    {
        if (this != &other)
        {
            int numVertices = V = other.V;
            graph = new double *[numVertices];

            for (size_t i = 0; i < numVertices; i++)
            {
                graph[i] = new double[numVertices];
                memcpy(graph[i], other.graph[i], sizeof(double) * numVertices);
            }
        }

        return *this;
    }

    void createLigation(int x, int y, double weight);
    int getV();
    double **getGraph();

    /* Funções uteis */
    void print();
    void newRandomGraph();
    void showResult();
    bool edgeExist(int x, int y);
};
