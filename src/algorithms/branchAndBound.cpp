#include <algorithm>
#include <stdio.h>
#include <string.h>

#include "../constants.h"
#include "../graph.h"
#include "branchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound() : TSP("Branch and Bound") {}
BranchAndBound::BranchAndBound(Graph &graph) : TSP(graph, "Branch and Bound") {}
BranchAndBound::BranchAndBound(Graph &&graph) : TSP(graph, "Branch and Bound") {}

/**
 * @brief Atualiza vetor com o melhor caminho.
 * 
 * @param caminhoParcial - Vetor auxiliar contendo o melhor caminho atual.
 */
void BranchAndBound::atualizarMelhorCaminho(int *caminhoParcial)
{
    int vertices = this->graph.getV();
    for (int x = 0; x < vertices; x++)
        this->cities[x] = caminhoParcial[x];
}

/**
 * @brief Encontra melhor caminho utilizando o algoritmo Branch and Bound
 * 
 * @param matriz - Matriz de adjacência (grafo)
 * @param parcial - Custo do caminho parcial
 * @param nivel - Nivel atual da árvore de recursão
 * @param caminhoParcial - Sequência de cidades parcorrida até o momento
 * @param visitados - Vetor com os vértices visitados
 */
void BranchAndBound::branchAndBound(double **matriz, double parcial, int nivel,
                                    int *caminhoParcial, bool *visitados)
{
    int vertices = this->graph.getV();
    int nivelAnterior = caminhoParcial[nivel - 1];

    // Se chegar no fim da árvore
    if (nivel == vertices)
    {
        // Testata se tem caminho direto de volta para
        // o vértice inicial
        if (matriz[nivelAnterior][caminhoParcial[0]] != UNDEFINED)
        {
            double resultadoAtual =
                parcial + matriz[nivelAnterior][caminhoParcial[0]];

            // Se o caminho percorrido até o fim da árvore é
            // menor que o menor atual, então podemos atribuí-lo
            // como o menor atual.
            if (resultadoAtual < this->distance)
            {
                atualizarMelhorCaminho(caminhoParcial);
                this->distance = resultadoAtual;
            }
        }
    }

    else
    {
        // Se ainda não chegou ao final da árvore,
        // continue percorrendo-a
        for (int x = 0; x < vertices; x++)
        {
            // Se a cidade não foi visitada e tem caminho entre os vertices
            if (!visitados[x] && matriz[nivelAnterior][x] != UNDEFINED)
            {
                parcial += matriz[nivelAnterior][x]; // salvar caminho anterior

                // Se o caminho parcial já é maior que o menor
                // caminho atual, então podemos descartar esta computação.
                if (parcial < this->distance)
                {
                    caminhoParcial[nivel] = x;
                    visitados[x] = true;
                    branchAndBound(matriz, parcial, nivel + 1, caminhoParcial,
                                   visitados);
                }

                parcial -= matriz[nivelAnterior][x];
                memset(visitados, false, vertices);
                for (int y = 0; y < nivel; y++)
                    visitados[caminhoParcial[y]] = true;
            }
        }
    }
}

void BranchAndBound::run()
{
    int vertices = this->graph.getV();
    int caminhoParcial[vertices + 1];
    bool visitados[vertices];
    double **matriz = this->graph.getGraph();

    this->distance = MAX;

    memset(caminhoParcial, -1, vertices + 1);
    memset(visitados, false, vertices);

    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(matriz, 0, 1, caminhoParcial, visitados);
}
