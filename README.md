# Traveling-Salesman-Problem

## 1) Introdução:
Em consonância com a expansão do mercado tecnológico, a complexidade dos problemas computacionais tem aumentado,
o que implicou na busca de máquinas mais potentes para processá-los. Entretanto, tais recursos são limitados 
e por isso devem ser utilizados de maneira eficiente. Tendo em vista esta problemática e com o objetivo de destacar a
importância do projeto e análise de algoritmos, o grupo propôs uma análise de quatro soluções distintas para um
problema clássico da Ciência da Computação, o Problema do Caixeiro Viajante (Traveling Salesman Problem).
Os algoritmos utilizados foram:


- Brute Force
    >Gera permutações de todos os caminhos possíveis e verifica dentre eles qual forma um
    ciclo e dos que formam um ciclo qual tem a menor distância
- Branch and Bound
    >Gera uma árvore com todos os caminhos testando todas as ramificações parciais e podando aquelas que
    já são maiores que a solução atual.
- Dynamic Programming
- Genetic Algorithm

## 2) Implementação:

### Descrição
Como o problema envolve naturalmente a estrutura de dados Grafo, todos os algoritmos a usam.
Neste trabalho criamos uma classe TSP (Traveling Salesman Problem) que serve como uma classe
abstrata e classe base para os outros algoritmos que também são representados por classes.

### Detalhes de implementação

#### Branch and Bound
Similar ao Brute Force, o Branch and Bound gera uma árvore de recursão com diversos caminhos para seguir. Entretanto, não 
gera todas as possibilidades para descobrir o melhor caminho, mas, a cada cidade que avança, o algoritmo compara se a soma 
das arestas passadas é maior que o melhor caminho atual. Caso o teste seja verdadeiro, o cálculo é abortado e o programa 
testa outro caminho na árvore de recursão descartando, assim, vários outros testes desnecessários.

A função principal do algoritmo possui os seguintes parâmetros:
- __double **matriz__: ponteiro para a matriz de adjacência(grafo);
- __double parcial__: tamanho do caminho parcial;
- __int nivel__: nível atual da árvore de recursão;
- __int *caminho_parcial__: ponteiro para vetor com os vértices do caminho atual na árvore de recursão;
- __bool *visitados__: ponteiro para vetor que representa vértices visitados;

O algoritmo começa inicializando os vetores __caminho_parcial__ e __visitados__. Logo após, passamos todos os parâmetros para 
o método principal. Sendo que __parcial__ é inicializado com __0__ e o __nivel__ se inicia com __1__. Assim, finalizadas as 
inicializações, podemos começar a analisar o método.
A ideia é bastante simples. No início do método, é testado se o algoritmo chegou ao último nível da árvore de recursão. Caso 
seja verdadeiro, se houver caminho direto até a raiz, somamos este caminho ao caminho parcial e testamos se esta soma é menor 
que a menor distância anterior. Se este teste também for verdadeiro, o vetor com o melhor caminho é atualizado e o seu custo 
é armazenado para futuras comparações. Veja abaixo o trecho:
```
if (nivel == vertices)									
{												
   if (matriz[nivelAnterior][caminhoParcial[0]] != UNDEFINED)			
   {											
      double resultadoAtual =							
         parcial + matriz[nivelAnterior][caminhoParcial[0]];		
         if (resultadoAtual < this→distance)					
         {										
            atualizarMelhorCaminho(caminhoParcial);			
            this->distance = resultadoAtual;					
         }										
   }											
}
```
Caso o algoritmo ainda não estiver no fim da árvore, o primeiro “if” será falso e, assim, cairemos no “eles”. Este bloco 
possui um “for” que passa por todos os vértices ainda não visitados. Em sua estrutura, temos uma chamada recursiva que é 
requisitada caso o custo do caminho parcial até o momento, __parcial__, seja menor que o custo do menor caminho atual. Porém, 
se esse teste for falso, ou seja, se o percorrido até este momento já é __maior__ que o menor caminho armazenado, o teste 
falha e, portanto, descartamos computações desnecessárias. 

Veja o código abaixo:
```
for (int x = 0; x < vertices; x++)
{
   if (!visitados[x] && matriz[nivelAnterior][x] != UNDEFINED)
   {
      parcial += matriz[nivelAnterior][x];
      if (parcial < this→distance)
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
```


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

### Branch and Bound
https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/<br />
https://www.youtube.com/watch?v=1FEP_sNb62k<br />

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
