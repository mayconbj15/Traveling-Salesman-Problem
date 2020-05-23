#include <algorithm>
#include <iostream>
#include <locale>
#include <math.h>
#include <memory>
#include <string.h>
#include <time.h>
#include <vector>

#include "TSP.h"
#include "algorithms/branchAndBound.h"
#include "algorithms/bruteForce.h"
#include "algorithms/dynamicProgramming.h"
#include "algorithms/geneticAlgorithm.h"
#include "arguments.h"
#include "constants.h"
#include "graph.h"

typedef pair<int, int> Vertice;

using namespace std;

/**
 * Função que executa um determinado algoritmo para o problema do Caixeiro Viajante e
 * mostra o resultado e suas estatisticas
 *
 * @param Graph o grafo que irá ser executado o Caixeiro Viajante
 */
template <typename Algorithm> double runAlgorithm(Graph &graph)
{
    TSP &&algorithm = Algorithm(graph);
    return algorithm.runAndCountTime();
}

/**
 * Função para debug das soluções
 */
template <typename Algorithm> void debug()
{
    Graph graph(10);

    graph.newRandomGraph();

    graph.print();

    runAlgorithm<Algorithm>(graph);
    DynamicProgramming(graph).run();
}

/**
 * Função que printa a média da execução de todos os algoritmos para
 * grafos com actualV vértices
 */
void printMeanTime(vector<unique_ptr<TSP>> &algorithms, int actualV)
{
    for (auto &&algorithm : algorithms)
    {
        if (!csvOutput)
        {
            cout << "MEDIA " << algorithm->getName() << " n = " << actualV << ": "
                 << algorithm->getTotalTime() / NUMBEROFGRAPHS << " ms" << endl;
        }
        else
        {
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

/**
 * Função que calcula a distância entre dois vértices
 *
 * @param v1 vértice inicial
 * @param v2 vértice final
 *
 * @return a distância entre os dois vértices
 */
double distBetweenVertexs(Vertice &v1, Vertice &v2)
{
    return sqrt(pow((v2.first - v1.first), 2) + pow((v2.second - v1.second), 2));
}

/** Cria um grafo completo com n(n-1)/2 arestas */
void createCompleteGraph(Graph &graph, vector<Vertice> &vertexs_set)
{
    double distance;
    int vertexs = graph.getV();

    for (int x = 0; x < vertexs; x++)
    {
        for (int y = 0; y < vertexs; y++)
        {
            distance = distBetweenVertexs(vertexs_set[x], vertexs_set[y]);
            graph.createLigation(x, y, distance);
        }
    }
}

#define DEBUG 0

/**
 * Função principal que recebe os parâmetros de qual algoritmo será executado,
 * lê as entradas e realiza as computações
 */
int main(int argc, char **argv)
{
#if DEBUG
    debug<DynamicProgramming>();
#else
    vector<unique_ptr<TSP>> algorithms;
    vector<Vertice> vertex_set;
    readArgs(argc, argv, algorithms);

    srand(time(NULL));
    int vertexs;
    int x, y, weight;

    int actualV = 3;

    while (scanf("%d", &vertexs) != EOF)
    {
        if (csvOutput) cout.setstate(ios_base::failbit);

        // calcula a média de tempo dos grafos calculados de V vertices
        if (actualV != vertexs)
        {
            printMeanTime(algorithms, actualV);
            actualV = vertexs;
        }

        Graph graph(vertexs);
        for (int i = 0; i < vertexs; i++)
        {
            cin >> x;
            cin >> y;
            vertex_set.push_back(make_pair(x, y));
        }

        createCompleteGraph(graph, vertex_set);

        // graph.print();

        for (const auto &algorithm : algorithms)
        {
            // Just run the code if we are using less than 15 cities or if
            // we are not using the brute force algorithm
            if (!(actualV == 15 &&
                  algorithm->getName().find("rute") != string::npos))
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
