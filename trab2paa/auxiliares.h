/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém a definição das funções auxiliares utilizadas.
 */

#ifndef __AUXILIARES__
#define __AUXILIARES__

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#include "structs.h"
#include "mergesort.h"

//============================================================//
//-------------------- FUNÇÕES AUXILIARES --------------------//
//============================================================//

/**
 * Função: order_vertice_arr
 *   Organiza o vetor que contem os vertices baseado no ângulo
 *   entre o pai, o filho e o ponto (0,0). Nela é contruida um 
 *   triângulo e o ângulo para a ordenação é obtido da distância
 *   de pai pra filho e distância de pai para o ponto (0,0). 
 *   O vetor é ordenado de forma decrescente.
 * 
 * Entradas:
 *   (const int) n: Tamanho do vetor de pontos e do vetor de vertice_arr.
 *   (Vertice*) vertice_arr: Vetor contendo os vertices da arvore AGM.
 *   (Point*) pts: Vetor contendo as posições x e y dos pontos.
 */
void order_vertice_arr(const int n, Vertice* vertice_arr, Point* pts);

/**
 * Função: gen_graph_list
 *   A partir do vetor de vertices que foram gerados pela AGM feita
 *   previamente, gera um grafo usando lista de adjacencia para fazer 
 *   a busca em profundidade. Antes da criação da lista, é chamada a 
 *   função order_vertice_arr para ordenar os vertices na tentativa 
 *   de melhorar os resultados obtidos na busca.
 * 
 * Entradas:
 *   (const int) n: Tamanho do vetor de pontos e do vetor de vertice_arr.
 *   (Vertice*) vertice_arr: Vetor contendo os vertices da arvore AGM.
 *   (Point*) pts: Vetor contendo as posições x e y dos pontos.
 * 
 * Saida:
 *   (Elemento*) graphList: Grafo em lista de adjacencia com vertices,
 *                          ordenados em sentido anti-horario.
 */
Elemento* gen_graph_list(const int n, Vertice* vertice_arr, Point* pts);

/**
 * Função: print_graph_list
 *   Exibir no terminal o grafo em lista de adjacencia.
 * 
 * Entradas:
 *   (const int) n: Quantidade de vertices do grafo.
 *   (Elemento*) graphList: Grafo em lista de adjacencia.
 */
void print_graph_list(const int n, Elemento* graphList);

/**
 * Função: dist
 *   Descobre a distancia entre dois pontos.
 * 
 * Entrada:
 *   (Point) p1: ponto 1.
 *   (Point) p2: ponto 2.
 * 
 * Saida:
 *   (float) distancia euclidiana entre dois pontos.
 */
float dist(Point p1, Point p2);

#endif