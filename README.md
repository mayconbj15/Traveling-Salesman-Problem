# Traveling-Salesman-Problem

## 1) Introdução:
Neste repositório iremos tratar o problema do Caixeiro Viajante. Para isso,
iremos implementar quatro tipos de algoritmos para resolvê-lo:

- Branch and Bound
- Brute Force
    >Gera permutações de todos os caminhos possíveis e verifica dentre eles qual forma um ciclo e dos que formam um ciclo qual tem a menor distância
- Dynamic Programming
- Genetic Algorithm

## 2) Implementação:

### Descrição
Como o problema envolve naturalmente a estrutura de dados Grafo, todos os algoritmos a usam.
Neste trabalho criamos uma classe TSP (Traveling Salesman Problem) que serve como uma classe
abstrata e classe base para os outros algoritmos que também são representados por classes.

### Detalhes de implementação
Métodos principais por classe:
- TSP
    - sumPath()

- BranchAndBound
    - sumPath()

- BruteForce
    - sumPath()

- DynamicProgramming
    - sumPath()

- GeneticAlgorithm
    - sumPath()

### Formato de entrada e saída

o formato de entrada e saída de dados, bem como decisões tomadas relativas aos
casos e detalhes de especificação que porventura estejam omissos no enunciado.

### Ambiente computacional

Sistema Operacional|Compilador                  |Editor de Código
-------------------|----------------------------|----------------
Windows/Linux      |gcc ou g++ que suporte c++14|Visual Studio Code

Para mais informações Linux/Mac:

```run.sh --help```

Para mais informações Windows, caso não tenha ativado a execução de scripts no PowerShell,
abra-o e rode ```Set-ExecutionPolicy Bypass Process```.

```run.ps1 --help```

## 3) Análise de Complexidade:
análise de complexidade do pior e do melhor caso de todas as
funções do programa e também do programa principal. Essa análise pode ser feita de forma
mais detalhada linha por linha, somando-se as complexidades ou de forma mais geral,
explicando a complexidade da função como um todo. De qualquer forma, tem que ficar claro
qual é a operação relevante e também as configurações de entrada que levam ao pior e ao
melhor caso.

## 4) Testes:
descrever os testes realizados, mostrando a saída do programa além de eventuais
análises e comparações que foram solicitadas no enunciado.

## 5) Conclusão:
comentários gerais sobre o trabalho e as principais dificuldades encontradas na
implementação.

## 6) Bibliografia:
bibliografia utilizada para o desenvolvimento do trabalho, incluindo sites da
internet se for o caso

## 7) Anexos:
listagem dos programas.
