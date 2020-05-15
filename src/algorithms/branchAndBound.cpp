#include <algorithm>
#include <string.h>

#include "../graph.h"
#include "../constants.h"
#include "branchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound(Graph graph) : TSP(graph, "Branch and Bound") {}

void BranchAndBound::atualizarMelhorCaminho(int* caminhoParcial)
{
    int vertices = this->graph.getV();
    for (int x = 0; x < vertices+1; x++)
        this->cities[x] = caminhoParcial[x];    
    
    this->cities[vertices] = caminhoParcial[0];    
}

void BranchAndBound::branchAndBound(
    int parcial, int nivel, int *caminhoParcial, bool *visitados, int menorCaminho)
{
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();
    int nivelAnterior = caminhoParcial[nivel - 1];

    if (nivel == vertices)
    {
        if (this->graph.getGraph())
        {
            if (matriz[nivelAnterior][caminhoParcial[0]] != 0)
            {
                int resultadoAtual = parcial + matriz[nivelAnterior][caminhoParcial[0]];

                // Se o caminho parcial já é maior que o menor
                // caminho atual, então podemos atualizar o melhor caminho.
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

void BranchAndBound::run()
{
    int vertices = this->graph.getV();
    int *caminhoParcial = new int[vertices + 1];
    int *melhorCaminho = new int[vertices + 1];
    bool *visitados = new bool[vertices];
    int menorCaminho = MAX;

    memset(caminhoParcial, -1, vertices + 1);
    memset(melhorCaminho, -1, vertices + 1);
    memset(visitados, false, vertices);

    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(0, 1, caminhoParcial, visitados, menorCaminho);
    showResult();
}
