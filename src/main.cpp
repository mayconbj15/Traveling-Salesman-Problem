#include <iostream>
#include <time.h>
#include <bits/stdc++.h>

#include "graph.h"
#include "constants.h"
#include "algorithms/branchAndBound.h"
#include "algorithms/bruteForce.h"
#include "algorithms/dynamicProgramming.h"
#include "algorithms/geneticAlgorithm.h"

using namespace std;

template <typename Algorithm>
double runAlgorithm(Graph &graph)
{
    return Algorithm(graph).runAndCountTime();
}

template <typename Algorithm>
double runAlgorithm(Graph &graph, double &timeTaken)
{
    double time = runAlgorithm<Algorithm>(graph);
    timeTaken += time;
    return time;
}

template <typename Algorithm>
void debug()
{
    Graph graph(4);

    graph.createLigation(0, 1, 10);
    graph.createLigation(0, 2, 15);
    graph.createLigation(0, 3, 20);
    graph.createLigation(1, 2, 35);
    graph.createLigation(1, 3, 25);
    graph.createLigation(2, 3, 30);

    /*
    Graph graph(10);

    graph.newRandomGraph();
    */

    graph.print();
    runAlgorithm<Algorithm>(graph);
}

int main()
{
    // debug<BranchAndBound>();

    srand(time(NULL));
    int vertexs, edges;
    int x, y, weight;

    int actualV = 3;

    double timeTaken = 0;

    while (scanf("%d %d", &vertexs, &edges) != EOF)
    {
        if (actualV != vertexs) //calcula a média de tempo dos grafos calculados de V vertices
        {
            cout << "MEDIA: " << timeTaken / NUMBEROFGRAPHS << endl;

            actualV = vertexs;
        }

        Graph graph(vertexs);
        for (int i = 0; i < edges; i++)
        {
            cin >> x;
            cin >> y;
            cin >> weight;

            graph.createLigation(x, y, weight);
        }

        //graph.print();

        runAlgorithm<BranchAndBound>(graph, timeTaken);
        cout << "----------------" << endl;
        runAlgorithm<BruteForce>(graph, timeTaken);
        cout << "----------------" << endl;
        runAlgorithm<GeneticAlgorithm>(graph, timeTaken);
        cout << "----------------" << endl;
    }
}
