#include "graph.h"
#include "TSP.h"

#include <iostream>
#include <bits/stdc++.h>
#include <stdint.h>

#define MAX 2147483647
#define UNDEFINED -1
#define ENDOFROUTE -1

using namespace std;

TSP::TSP(Graph graph)
{
    this->graph = graph;
    this->cities = new int[graph.getV()];
    this->distance = MAX;
}

void printArray(int *array, int n)
{
    for (int i = 0; i < n; i++)
        cout << array[i] << " ";
    cout << endl;
}

void TSP::showResult()
{
    cout << "V: " << this->graph.getV() << endl;
    cout << "Shortest distance: " << distance << endl;
    cout << "Shortest path:" << endl;

    for (int i = 0; i < graph.getV(); i++)
        cout << cities[i] << " ";

    cout << endl;
}

/**
 * Função que gera um conjunto de vértices padrão que será permutado
 * 
 * @return um array com de 0 a V
 */
int *TSP::initializePath(int *paths, int V)
{
    int i = 0;
    for (i = 0; i < V; i++)
        paths[i] = i;
    paths[i] = 0;

    return paths;
}

/**
 * Função principal do algoritmo do Caixeiro Viajante usando Força Bruta
 */
void TSP::bruteForce()
{
    int V = this->graph.getV();

    int *paths = new int[V + 1];

    // Gera um vetor com os vertices que serão permutados
    paths = initializePath(paths, V);

    permutation(paths, V, V);

    showResult();
}

/**
 * Função que recebe um array de inteiros e gera suas permutações
 *  do elemento 1 ao n-1, mantendo o primeiro elemento fixo
 * 
 * @param array array de inteiro a serem permutados
 * @param size tamanho lógico do vetor de array atual
 * @param n tamanho real do vetor
 * 
 */
void TSP::permutation(int array[], int size, int n)
{
    if (size == 1) //final da permutação
    {
        walkThePath(array);
        return;
    }

    for (int i = 1; i < size; i++)
    {
        permutation(array, size - 1, n);

        if (size % 2 == 1)
            swap(array[1], array[size - 1]);
        else
            swap(array[i], array[size - 1]);
    }
}

/**
 * Função que percorre um determinado conjunto de vertices dado em um array de inteiro
 * e faz a soma de seus pesos
 * 
 * @param array array de inteiro com os vértices a serem visitados
 */
void TSP::walkThePath(int *array)
{
    double sum = 0.0;
    int V = this->graph.getV();
    double **graphMatrix = this->graph.getGraph();

    int i = 0;
    int j = 1;
    for (; j < V + 1; i++, j++)
    {
        if (graphMatrix[array[i]][array[j]] != UNDEFINED)
        {
            sum += graphMatrix[array[i]][array[j]];
        }

        else
        {
            return; //O caminho não gera um ciclo hamiltoniano
        }
    }

    if (sum < this->distance)
    {
        this->distance = sum;

        //preenche o vetor de cidades com o maior caminho
        for (int i = 0; i < V; i++)
            this->cities[i] = array[i];
    }
}

void TSP::branchAndBound()
{
    int vertices = this->graph.getV();
    int *caminhoParcial = new int[vertices + 1];
    bool *visitados = new bool[vertices];
    int menorCaminho = MAX;

    memset(caminhoParcial, -1, vertices + 1);
    memset(visitados, false, vertices);

    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(0, 1, caminhoParcial, visitados, menorCaminho);
}

void TSP::branchAndBound(int parcial, int nivel, int *caminhoParcial, bool *visitados, int menorCaminho)
{
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();

    if (nivel == vertices)
    {
        if (this->graph.getGraph())
        {
            if (matriz[caminhoParcial[nivel-1]][caminhoParcial[0]] != 0)
            {
                
                int resultadoAtual = parcial + matriz[caminhoParcial[nivel - 1]][caminhoParcial[0]];

                if (resultadoAtual < menorCaminho)
                {
                    atualizarMelhorCaminho(caminhoParcial);
                    menorCaminho = resultadoAtual;
                }
            }
        }
    }
    else
    {
        // Percorrer cidades
        for (int x = 0; x < vertices; x++)
        {
            int nivelAnterior = caminhoParcial[nivel - 1];

            // Se a cidade não foi visitada e tem caminho entre os vertices
            if (!visitados[x] && matriz[nivelAnterior][x] != 0)
            {
                parcial += matriz[nivelAnterior][x];

                // Se o caminho parcial já é maior que o menor
                // caminho atual, então podemos descartar esta computação.
                if (parcial < menorCaminho)
                {
                    caminhoParcial[nivel] = x;
                    visitados[x] = true;
                    branchAndBound(parcial, nivel + 1, caminhoParcial, visitados, menorCaminho);
                }

                parcial -= matriz[nivelAnterior][x];

                memset(visitados, false, vertices);
                for (int y = 0; y < nivel; y++)
                    visitados[caminhoParcial[y]] = true;
            }
        }
    }
}

//void TSP::
/**
 * Based on https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/
 */
void TSP::geneticAlgorithm()
{
    int numVertices = this->graph.getV();
    // int verticesIndexes = createChromosome(numVertices);
}
