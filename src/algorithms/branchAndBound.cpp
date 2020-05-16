#include <algorithm>
#include <string.h>

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

int BranchAndBound::primeiroMenor(int vertice)
{
    int menor = MAX;
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();

    for (int x = 0; x < vertices; x++)
    {
        if (vertice != x && matriz[vertice][x] < menor)
            menor = matriz[vertice][x];
    }
    return menor;
}

int BranchAndBound::segundoMenor(int vertice)
{
    int primeiro_menor = MAX, segundo_menor = MAX;
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();

    for (int x = 0; x < vertices; x++)
    {
        if (x != vertice && matriz[vertice][x] <= primeiro_menor)
        {
            segundo_menor = primeiro_menor;
            primeiro_menor = matriz[vertice][x];
        }
        else
        {
            if (matriz[vertice][x] <= segundo_menor && matriz[vertice][x] != primeiro_menor)
                segundo_menor = matriz[vertice][x];
        }
    }
    return segundo_menor;
}

void BranchAndBound::branchAndBound(
    int parcial, int nivel, int *caminhoParcial, bool *visitados)
{
    int vertices = this->graph.getV();
    double **matriz = this->graph.getGraph();
    int nivelAnterior = caminhoParcial[nivel - 1];

    // Se chegar no fim da árvore
    if (nivel == vertices)
    {
        // Testata se tem caminho direto de volta para
        // o vértice inicial
        if (matriz[nivelAnterior][caminhoParcial[0]] != 0)
        {
            int resultadoAtual = parcial + matriz[nivelAnterior][caminhoParcial[0]];

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
            if (!visitados[x] && matriz[nivelAnterior][x] != 0)
            {
                parcial += matriz[nivelAnterior][x]; // salvar caminho anterior
                            
                // Se o caminho parcial já é maior que o menor
                // caminho atual, então podemos descartar esta computação.
                if (parcial < this->distance)
                {
                    caminhoParcial[nivel] = x;
                    visitados[x] = true;
                    branchAndBound(parcial, nivel + 1, caminhoParcial, visitados);
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
    int menorCaminho = MAX;
    int *caminhoParcial = new int[vertices + 1];
    bool *visitados = new bool[vertices];

    memset(caminhoParcial, -1, vertices + 1);
    memset(visitados, false, vertices);    
    
    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(0, 1, caminhoParcial, visitados);
}
