/**
 * Travelling Salesman Problem implementations:
 * - Brute force
 * - Branch and bound
 * - Dynamic programming
 * - Genetic algorithm
 */
class TSP
{
private:
    Graph graph;

    double distance;
    int *cities;

    /* Funções auxiliares do paradigma de Força Bruta */
    void permutation(int array[], int size, int n);
    void walkThePath(int *array);
    double sumPath(int *array);
    void showResult();
    int *initializePath(int *paths, int V);

    /* Funções auxiliares do paradigma de Força Bruta */
    void branchAndBound(int parcial, int nivel, int* caminhoParcial, bool* visitados, int menorCaminho);
    void atualizarMelhorCaminho(int* caminhoParcial);

public:
    TSP(Graph graph);

    /* Funções dos algoritmos dos paradigmas */
    void bruteForce();
    void branchAndBound();
    void geneticAlgorithm();
};