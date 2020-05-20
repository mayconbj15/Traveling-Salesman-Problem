# Traveling-Salesman-Problem

## 1) Introdução:
Neste repositório iremos tratar o problema do Caixeiro Viajante. Para isso,
iremos implementar quatro tipos de algoritmos para resolvê-lo:

- Branch and Bound
- Brute Force
    >Gera permutações de todos os caminhos possíveis e verifica dentre eles qual forma um
    ciclo e dos que formam um ciclo qual tem a menor distância
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

```./run.sh --help```

Para mais informações Windows, caso não tenha ativado a execução de scripts no PowerShell,
abra-o e rode ```Set-ExecutionPolicy Bypass Process```.

```./run.ps1 --help```

Rodando todos os algoritmos Linux/Mac:

```./run.sh branch brute dynamic genetic```

Rodando todos os algoritmos Windows:

```./run.ps1 branch brute dynamic genetic```

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

Em todos os gráficos, o eixo x é o número de cidades e o eixo y é o tempo gasto em milisegundos.

![travelling salesman problem, branch and bound, brute force, dynamic programming, genetic algorithm](https://i.imgur.com/O8PazIL.png)

![travelling salesman problem, branch and bound, dynamic programming, genetic algorithm](https://i.imgur.com/Ditn469.png)

![travelling salesman problem, dynamic programming, genetic algorithm](https://i.imgur.com/IRRMCS8.png)

## 5) Conclusão:
O trabalho foi muito bom para o grupo. Pudemos melhorar nossas habilidades na programação
de algoritmos e também melhorar o nosso raciocínio lógico.

As principais dificuldades que tivemos foram nos algoritmos de Branch and Bound e Dynamic
Programming. Porém, foi muito interessante tentar enxergar a sobreposição de problemas no
algoritmo de Dynamic Programming. Além disso, pensar em como guardar os resultados dos
subproblemas também foi bem interessante.

## 6) Bibliografia:
#### Força Bruta
https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/<br/>
https://www2.cs.sfu.ca/CourseCentral/125/tjd/tsp_example.html

#### Algoritmo Genético
https://www.geeksforgeeks.org/traveling-salesman-problem-using-genetic-algorithm/

#### Programação Dinâmica
https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/<br/>
https://www.youtube.com/watch?v=Q4zHb-Swzro<br/>
https://www.youtube.com/watch?v=cY4HiiFHO1o<br/>
https://www.youtube.com/watch?v=udEe7Cv3DqU<br/>
https://www.youtube.com/watch?v=-JjA4BLQyqE<br/>
https://www.youtube.com/watch?v=JE0JE8ce1V0

#### Gerais
https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/<br/>
https://www.ime.usp.br/~pf/analise_de_algoritmos/aulas/NPcompleto.html


## 7) Anexos:
#### Repositório
https://github.com/mayconbj15/Traveling-Salesman-Problem
