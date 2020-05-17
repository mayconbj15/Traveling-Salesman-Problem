#include <algorithm>
#include <string.h>
#include <stdio.h>

#include "../graph.h"
#include "../constants.h"
#include "branchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound() : TSP("Branch and Bound") {}
BranchAndBound::BranchAndBound(Graph &graph) : TSP(graph, "Branch and Bound") {}
BranchAndBound::BranchAndBound(Graph &&graph) : TSP(graph, "Branch and Bound") {}

void BranchAndBound::atualizarMelhorCaminho(int *caminhoParcial)
{
    int vertices = this->graph.getV();
    for (int x = 0; x < vertices; x++)
        this->cities[x] = caminhoParcial[x];
}

void BranchAndBound::branchAndBound(
    double** matriz, double parcial, int nivel, int *caminhoParcial, bool *visitados)
{
    int vertices = this->graph.getV();    
    int nivelAnterior = caminhoParcial[nivel - 1];
    // printf("%lf \n", this->distance);
    // Se chegar no fim da árvore
    if (nivel == vertices)
    {
        // Testata se tem caminho direto de volta para
        // o vértice inicial
        if (matriz[nivelAnterior][caminhoParcial[0]] != UNDEFINED)
        {
            double resultadoAtual = parcial + matriz[nivelAnterior][caminhoParcial[0]];

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
                    branchAndBound(matriz, parcial, nivel + 1, caminhoParcial, visitados);
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
    this->distance = MAX;
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();
    int *caminhoParcial = new int[vertices + 1];
    bool *visitados = new bool[vertices];

    memset(caminhoParcial, -1, vertices + 1);
    memset(visitados, false, vertices);    
    
    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(matriz, 0, 1, caminhoParcial, visitados);
    delete[] caminhoParcial;
    delete[] visitados;
}
