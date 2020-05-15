#include <iostream>
#include <time.h>
#include <bits/stdc++.h>

#include "graph.h"
#include "TSP.h"

using namespace std;

#define UNDEFINED -1
#define ENDOFROUTE -1
#define EXECUTIONS 10
#define NUMBEROFGRAPHS 15

void printClock(clock_t start, clock_t end, string msg);

void debug()
{
    /*  Graph graph(5);

    graph.createLigation(0, 1, 3);
    graph.createLigation(0, 2, 6);
    graph.createLigation(2, 3, 5);
    graph.createLigation(3, 1, 4);
    graph.createLigation(0, 3, 5);
    graph.createLigation(1, 2, 7);
    graph.createLigation(2, 4, 3);
    graph.createLigation(4, 3, 5); */

    Graph graph(10);

    graph.newRandomGraph();

    graph.print();
    TSP bruteForce(graph);

    clock_t start, end;

    //cout << "STARTING BRUTE FORCE" << endl;
    start = clock();
    bruteForce.bruteForce();
    end = clock();
    printClock(start, end, "Time elapsed of Brute Force");
}

void printClock(clock_t start, clock_t end, string msg)
{
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << msg << ": " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

int main()
{
    //debug();
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
            if (vertexs == 12)
                return 0;
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

        TSP tsp(graph);

        clock_t start, end;
        start = clock();
        tsp.bruteForce();
        end = clock();

        timeTaken += double(end - start);

        printClock(start, end, "Time elapsed of Brute Force");
    }
}