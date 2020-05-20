#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <string.h>
#include <locale>
#include <memory>

#include "graph.h"
#include "TSP.h"
#include "constants.h"
#include "arguments.h"
#include "algorithms/branchAndBound.h"
#include "algorithms/bruteForce.h"
#include "algorithms/dynamicProgramming.h"
#include "algorithms/geneticAlgorithm.h"

using namespace std;

template <typename Algorithm>
double runAlgorithm(Graph &graph)
{
    TSP &&algorithm = Algorithm(graph);
    return algorithm.runAndCountTime();
}

template <typename Algorithm>
void debug()
{
    Graph graph(4);

    graph.createLigation(0, 1, 3);
    graph.createLigation(0, 2, 1);
    graph.createLigation(0, 3, 2);
    graph.createLigation(1, 2, 7);
    graph.createLigation(1, 3, 4);
    graph.createLigation(2, 3, 5);

    /*
    Graph graph(10);

    graph.newRandomGraph();
    */

    graph.print();

    runAlgorithm<Algorithm>(graph);
    // DynamicProgramming(graph).run();
}

void printMeanTime(vector<unique_ptr<TSP>> &algorithms, int actualV)
{
    for (auto &&algorithm : algorithms)
    {
        if (!csvOutput) {
            cout << "MEDIA " << algorithm->getName()
                << " n = " << actualV << ": "
                << algorithm->getTotalTime() / NUMBEROFGRAPHS << " ms" << endl;
        }
        else {
            cout.clear();
            cout << algorithm->getTotalTime() / NUMBEROFGRAPHS << ",";
            cout.setstate(ios_base::failbit);
        }

        algorithm->setTotalTime(0);
    }
    if (csvOutput) cout.clear();
    cout << endl;
    if (csvOutput) cout.setstate(ios_base::failbit);
}

#define DEBUG 0

int main(int argc, char **argv)
{
    #if DEBUG
    debug<DynamicProgramming>();
    #else
    vector<unique_ptr<TSP>> algorithms;
    readArgs(argc, argv, algorithms);

    srand(time(NULL));
    int vertexs, edges;
    int x, y, weight;

    int actualV = 3;
    
    while (scanf("%d %d", &vertexs, &edges) != EOF)
    {
        if (csvOutput) cout.setstate(ios_base::failbit);
        if (actualV != vertexs) //calcula a média de tempo dos grafos calculados de V vertices
        {
            printMeanTime(algorithms, actualV);
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

        // graph.print();

        for (const auto &algorithm : algorithms)
        {
            // Just run the code if we are using less than 15 cities or if
            // we are not using the brute force algorithm
            if (!(actualV == 15 && algorithm->getName().find("rute") != string::npos))
            {
                algorithm->setGraph(graph);
                algorithm->runAndCountTime();
                if (!csvOutput) cout << "----------------" << endl;
            }
        }
    }
    printMeanTime(algorithms, actualV);
    #endif
}
