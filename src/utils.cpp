#include <iostream>
#include <time.h>

#define N 15

using namespace std;

/**
 * Função que gera um formato de entrada de Grafo em que as linhas representam
 * arestas
 */
void generateInput()
{
    int n = 3;

    double number;

    srand(time(NULL));

    for (; n <= 15; n += 3)
    {
        int edges = (n * (n - 1)) / 2; // número de arestas de um vertice completo

        // gera N grafos de tamanho n
        for (int graphs = 0; graphs < N; graphs++)
        {
            cout << n << " " << edges << endl;
            // gera uma entrada de grafo aleatoria
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i != j && j > i)
                        cout << i << " " << j << " " << (double)(rand() % 10 + 1)
                             << endl;
                }
            }
            cout << endl;
        }

        cout << endl;
    }
}

/**
 * Função que gera um formato de entrada de Grafo em que as linhas representam
 * vértices
 */
void generateInputV2()
{
    int numero_de_casos = 1000;
    int cidades = 0;
    int x = 0, y = 0;

    for (int cidades = 3; cidades <= N; cidades += 3)
    {
        for (int casos = 0; casos < N; casos++)
        {
            printf("%d \n", cidades);

            for (int coordenadas = 0; coordenadas < cidades; coordenadas++)
            {
                x = rand() % 1000, y = rand() % 1000;
                printf("%d %d\n", x, y);
            }
        }
        printf("\n");
    }
}
