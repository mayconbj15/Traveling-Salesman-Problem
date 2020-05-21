#include <iostream>
#include <time.h>

#define N 15;

using namespace std;

void generateInput()
{
    int n = 3;

    double number;

    srand(time(NULL));

    for (; n <= 15; n += 3)
    {
        int edges = (n * (n - 1)) / 2; //número de arestas de um vertice completo

        //gera N grafos de tamanho n
        for (int graphs = 0; graphs < N graphs++)
        {
            cout << n << " " << edges << endl;
            //gera uma entrada de grafo aleatoria
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i != j && j > i)
                        cout << i << " " << j << " " << (double)(rand() % 10 + 1) << endl;
                }
            }
            cout << endl;
        }

        cout << endl;
    }
}

void generateInputV2()
{
    int numero_de_casos = 1000;
    int cidades = 0;
    int x = 0, y = 0;

    for (int casos = 0; casos < numero_de_casos; casos++)
    {
        cidades = rand() % 100; // gerar numero de cidades do caso
        printf("%d \n", cidades);

        for (int coordenadas = 0; coordenadas < cidades; coordenadas++)
        {
            x = rand() % 1000, y = rand() % 1000;
            printf("%d %d", x, y);
        }
    }
}