#include <iostream>

#include "graph.h"
#include "TSP.h"

using namespace std;

#define UNDEFINED -1
#define ENDOFROUTE -1

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

    Graph graph(20);

    graph.newRandomGraph();

    graph.print();
    TSP bruteForce(graph);

    cout << "COMPUTING..." << endl;
    bruteForce.bruteForce();

    cout << "END" << endl;
}

int main()
{
    debug();
    int vertexs, edges;
    int x, y, weight;
    cin >> vertexs;
    cin >> edges;

    Graph graph(vertexs);

    for (int i = 0; i < edges; i++)
    {
        cin >> x;
        cin >> y;
        cin >> weight;

        graph.createLigation(x, y, weight);
    }

    graph.print();

    TSP brute(graph);

    brute.bruteForce();
}