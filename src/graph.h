#pragma once

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

    void createLigation(int x, int y, double weight);
    int getV();
    double **getGraph();

    /* Funções uteis */
    void print();
    void newRandomGraph();
    void showResult();
    bool edgeExist(int x, int y);
};
