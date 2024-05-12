/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as definições das funções principais desenvolvidas.
 */

#ifndef __PRINCIPAIS__
#define __PRINCIPAIS__

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "structs.h"
#include "heap.h"

//============================================================//
//-------------------- FUNÇÕES PRINCIPAIS --------------------//
//============================================================//

/**
 * Função: gen_graph_mat
 *   Gera um grafo completo armazenado em uma matriz à partir de
 *   um vetor de n pontos. Cada aresta é representada pela dis-
 *   tância euclidiana entre dois vértices do grafo.
 * 
 * Complexidade:
 *   Por preencher totalmente uma matriz de tamanho nxn, a com-
 *   plexidade da função é da ordem de O(n^2).
 * 
 * Entradas:
 *   (int) n: Número de pontos presentes no vetor de pontos pts.
 *   (Point*) pts: Vetor de pontos.
 * 
 * Saídas:
 *   (float**) graphMat: Grafo completo armazenado em uma matriz 
 *                       de tamanho nxn. 
 */
float** gen_graph_mat(const int n, Point* pts);

/**
 * Função: AGM_Prim
 *   Encontra a AGM de um grafo em forma de matriz de adjacências 
 *   utilizando o algoritmo de Prim e armazenando os vértices a 
 *   serem visitados com um heap mínimo.
 * 
 * Descrição do algoritmo:
 *   De maneira geral, o algoritmo de Prim computa uma Árvore
 *   Geradora Mínima (AGM) de um grafo dado escolhendo a menor
 *   aresta saindo de um corte C, que inicialmente só compreende
 *   o vértice inicial, e adicionando o vértice que se visita com
 *   a aresta ao corte. Isso se repete até que o corte compreenda
 *   todo o grafo. 
 * 
 *   Uma das implementações possíveis, adotada nesse trabalho,
 *   utiliza de um heap mínimo para guardar as arestas do grafo, 
 *   a fim de melhorar o desempenho do algoritmo. Isso é atingido
 *   por conta da dinâmica do heap que permite reduzir a complexi-
 *   dade da escolha do próximo vértice a ser incluído no corte. 
 * 
 *   A implementação algoritmo se inicia criando o heap mínimo com 
 *   todos os vértices do grafo, de forma que o custo (chave do 
 *   heap) de todos os vértices seja "infinito", com exceção daquele 
 *   onde se inicia o algoritmo, que recebe custo 0. 
 *
 *   Feito isso, é iniciado um loop até que o heap esteja vazio em 
 *   que se retira a menor chave u do heap, e se verificam todos
 *   os vértices adjacentes àquele retirado (por se tratar de um 
 *   grafo completo, são vistos todos os vértices que ainda estão 
 *   no heap). 
 *   
 *   Cada vértice v encontrado através de uma aresta e = (u,v) 
 *   terá seu custo alterado caso v.custo > Ce. No caso desse valor 
 *   se alterar, por ser sempre um valor menor, há a necessidade de 
 *   se reorganizar o heap a fim de manter a propriedade de um heap 
 *   mínimo. Além disso, toda vez que o custo de um vértice é alte-
 *   rado, esse vértice guarda o seu vértice pai, a fim de podermos 
 *   reconstruir a AGM após o fim do algoritmo. 
 * 
 * Complexidade:
 *   As partes mais complexas do algoritmo são a extração da chave 
 *   mínima e a reorganização do heap após a redução de uma chave,
 *   executando respectivamente nas ordens de O(nlgn) e O(mlgn), 
 *   sendo n o número de vértices e m o número de arestas. 
 * 
 *   Esses valores se originam no fato de a reorganização do heap 
 *   ser executada em O(lgn), sendo que a extração de chave exige
 *   que o heap se reorganize uma vez para cada vértice do grafo e
 *   a diminuição de uma chave pode ocorrer um número de vezes da
 *   ordem do número m de arestas do grafo.
 * 
 *   Dito isso, sabemos que o algoritmo é da ordem de O((n+m)lgn).
 *   Porém, como tratamos de um grafo completo, o valor de m é da
 *   ordem de n^2, fazendo com que o algoritmo fique com uma com-
 *   plexidade da ordem de O((n^2)lgn).
 *    
 * Adaptações realizadas:
 *   A principal adaptação realizada foi para tratar o grafo com 
 *   uma representação em matriz de adjacências. Para que fosse
 *   possível conferir os custos guardados no grafo, foi preciso
 *   fazer com que cada vértice guardasse um índice que permitisse
 *   identificar únicamente a qual ponto ele se referia, o que se
 *   reflete nas linhas/colunas da matriz de adjacências que con-
 *   tém os custos referentes ao dado vértice. 
 * 
 * Entradas:
 *   (float**) graph_mat: grafo em uma matriz de adjacências.
 *   (const int) n: número de vértices do grafo.
 *   (int) index: índice do primeiro vértice a ser visitado.
 * 
 * Saídas:
 *   (Vertice*) vertice_arr: vetor de vértices que contém todos os 
 *                           vértices do grafo com seus respectivos
 *                           custos e pais. 
 */
Vertice* AGM_Prim(float** graph_mat, int n, int index);

/**
 * Função: busca_profundidade
 *   Realiza uma busca em profundidade modificada na AGM definida
 *   por uma lista de adjacências a fim de estabelecer um ciclo.
 *   
 * Descrição do algoritmo:
 *   O algoritmo de busca implementado navega pela AGM computada
 *   previamente e toda vez que chega a um vértice novo o adiciona
 *   a um vetor que contém os índices, em ordem, dos pontos que
 *   formam o ciclo procurado. Feito isso, é chamada a função de 
 *   busca recursivamente para cada aresta da lista de adjacências 
 *   do vértice, até que toda a AGM seja percorrida. Tendo sido 
 *   finalizada a execução do algoritmo, é necessário se incluir o 
 *   ponto inicial novamente, a fim de fechar o ciclo.
 * 
 * Complexidade:
 *   Por ser derivada da busca em profundidade, a complexidade do
 *   algoritmo é da ordem de O(n+m). Por ser realizada numa AGM, 
 *   o número de arestas é exatamente n-1, fazendo com que, na
 *   prática, a complexidade do algoritmo seja da ordem de O(n).
 *  
 * Adaptações realizadas:
 *   A maior adaptação realizada foi para permitir guardar o ciclo
 *   computado pela busca. Foi alocado um vetor de n+1 posições
 *   anteriormente ao início da busca, que é preenchido conforme
 *   a AGM vai sendo navegada. 
 * 
 *   Além disso, para garantir que a sequência do ciclo seja 
 *   mantida mesmo com as chamadas recursivas, o índice do vetor 
 *   que guarda o ciclo teve de ser criado externamente à função 
 *   de busca.
 * 
 * Entradas:
 *   (Elemento*) graphList: AGM armazenada como um grafo em lista
 *                          de adjacências.
 *   (int) index: índice do vértice sendo visitado.
 *   (int*) cycle: vetor que armazena o ciclo a ser computado.
 *   (int*) cycle_idx: índice da posição a ser preenchida do vetor
 *                     cycle.
 * 
 * Saídas:
 *   (int*) cycle: vetor preenchido com o ciclo computado após a 
 *                 finalização do algoritmo. 
 */
void busca_profundidade(Elemento* graphList,int index, int* cycle, int* cycle_idx);


#endif