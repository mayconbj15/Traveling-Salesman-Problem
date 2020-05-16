#include <algorithm>
#include <string.h>

#include "../graph.h"
#include "../constants.h"
#include "bruteForce.h"

using namespace std;

BruteForce::BruteForce(Graph graph) : TSP(graph, "Brute Force") {}

/**
 * Função que gera um conjunto de vértices padrão que será permutado
 * 
 * @return um array com de 0 a V
 */
int *BruteForce::initializePath(int *paths, int V)
{
    int i = 0;
    for (i = 0; i < V; i++)
        paths[i] = i;
    paths[i] = 0;

    return paths;
}

/**
 * Função que percorre um determinado conjunto de vertices dado em um array de inteiro
 * e faz a soma de seus pesos
 * 
 * @param array array de inteiro com os vértices a serem visitados
 */
void BruteForce::walkThePath(int *array)
{
    int V = this->graph.getV();
    double sum = sumPath(array);

    if (sum == -1)
        return;
    if (sum < this->distance)
    {
        this->distance = sum;

        //preenche o vetor de cidades com o maior caminho
        for (int i = 0; i < V; i++)
            this->cities[i] = array[i];
    }
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
void BruteForce::permutation(int array[], int size, int n)
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
 * Função principal do algoritmo do Caixeiro Viajante usando Força Bruta
 */
void BruteForce::run()
{
    int V = this->graph.getV();

    int *paths = new int[V + 1];

    // Gera um vetor com os vertices que serão permutados
    paths = initializePath(paths, V);

    permutation(paths, V, V);
}