class TSP
{
private:
    Graph graph;

    double distance;
    int *cities;

    /* Funções auxiliares do paradigma de Força Bruta */
    void permutation(int array[], int size, int n);
    void walkThePath(int *array);
    void showResult();
    int *initializePath(int *paths, int V);

public:
    TSP(Graph graph);

    /* Funções dos algoritmos dos paradigmas */
    void bruteForce();
};