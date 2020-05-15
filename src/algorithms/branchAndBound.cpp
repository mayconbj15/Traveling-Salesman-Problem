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

int BranchAndBound::primeiroMenor(int vertice) 
{
    int menor = MAX;
    int vertices = this->graph.getV();
    double** matriz = this->graph.getGraph();

    for(int x = 0; x < vertices; x++)
    {        
        if(vertice != x && matriz[vertice][x] < menor)
            menor = matriz[vertice][x];
    }
    return menor; 
}

int BranchAndBound::segundoMenor(int vertice) 
{
    int primeiro_menor = MAX, segundo_menor = MAX;
    int vertices = this->graph.getV();
    double** matriz = this->graph.getGraph();

    for (int x = 0; x < vertices; x++)
    {
        if(x != vertice && matriz[vertice][x] <= primeiro_menor)
        {
            segundo_menor = primeiro_menor;
            primeiro_menor = matriz[vertice][x];
        }
        else
        {
            if(matriz[vertice][x] <= segundo_menor && matriz[vertice][x] != primeiro_menor)
                segundo_menor = matriz[vertice][x];
        }
    }
    return segundo_menor;
}

void BranchAndBound::branchAndBound(
    int parcial, int nivel, int limite_atual, int *caminhoParcial, bool *visitados)
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
                if (resultadoAtual < this->distance)
                {
                    atualizarMelhorCaminho(caminhoParcial);
                    this->distance = resultadoAtual;
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
                int aux = limite_atual;
                parcial += matriz[nivelAnterior][x];

                if(nivel == 1)
                    limite_atual -= primeiroMenor(caminhoParcial[nivel-1]) + primeiroMenor(x)/2;
                else
                    limite_atual -= segundoMenor(caminhoParcial[nivel-1]) + primeiroMenor(x)/2;

                // Se o caminho parcial já é maior que o menor
                // caminho atual, então podemos descartar esta computação.
                if (parcial + limite_atual < this->distance)
                {
                    caminhoParcial[nivel] = x;
                    visitados[x] = true;
                    branchAndBound(parcial, nivel + 1, limite_atual, caminhoParcial, visitados);
                }

                parcial -= matriz[nivelAnterior][x];
                limite_atual = aux;

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
    int limite_atual = 0;

    memset(caminhoParcial, -1, vertices + 1);
    memset(melhorCaminho, -1, vertices + 1);
    memset(visitados, false, vertices);

    for (int x = 0; x < vertices; x++)
        limite_atual += (primeiroMenor(x) + segundoMenor(x));
    limite_atual = (limite_atual & 1)? limite_atual/2 + 1 : limite_atual/2;

    visitados[0] = true;
    caminhoParcial[0] = 0;

    branchAndBound(0, 1, limite_atual, caminhoParcial, visitados);
    showResult();
}
