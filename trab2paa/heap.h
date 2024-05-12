/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as definições das funções atreladas ao uso do Heap.
 */

#ifndef __HEAP__
#define __HEAP__

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "structs.h"

//============================================================//
//--------------------------- HEAP ---------------------------//
//============================================================//

/**
 * Função: Parent
 *   Retorna o índice do pai do Vertice indexado por i no vetor 
 *   do heap.
 * 
 * Entradas:
 *   (int) i: Índice do Vertice do qual queremos descobrir o pai.
 * 
 * Saídas:
 *   (int) i/2: Índice do pai.
 */
int Parent(int i);

/**
 * Função: Left
 *   Retorna o índice do filho à esquerda do Vertice indexado
 *   por i no vetor do heap.
 * 
 * Entradas:
 *   (int) i: Índice do Vertice do qual queremos o filho.
 * 
 * Saídas:
 *   (int) 2*i: Índice do filho à esquerda.
 */
int Left(int i);

/**
 * Função: Right
 *   Retorna o índice do filho à direita do Vertice indexado
 *   por i no vetor do heap.
 * 
 * Entradas:
 *   (int) i: Índice do Vertice do qual queremos o filho.
 * 
 * Saídas:
 *   (int) 2*i+1: Índice do filho à direita.
 */
int Right(int i);

/**
 * Função: Min_Heapify
 *   Atualiza o heap mínimo, reorganizando-o recursivamente até
 *   o vetor interno do heap estar devidamente ordenado de forma
 *   a manter a propriedade de heap mínimo. A ordenação é feita 
 *   com base no custo das arestas para se chegar em cada vertice.
 * 
 * Entradas:
 *   (Heap*) heap: O heap a ser atualizado.
 *   (int) i: Índice do elemento do heap a ser avaliado no momento.
 */
void Min_Heapify(Heap* heap, int i);

/**
 * Função: Build_Min_Heap
 *   Cria o heap mínimo de tamanho n, ordenado com base no custo
 *   das arestas para se chegar em cada vertice, conforme presente
 *   no vetor de vértices vindo da entrada.
 * 
 * Entradas:
 *   (Vertice*) array: vetor de vertices.
 *   (int) n: tamanho do vetor de vertices.
 * 
 * Saídas:
 *   (Heap) heap: heap mínimo gerado.
 */
Heap Build_Min_Heap(Vertice* array, int n);

/**
 * Função: Heap_Extract_Min
 *   Extrai e retorna o menor elemento, presente no índice 0 do vetor 
 *   do heap, e então diminui o tamanho atual do heap, atualizando 
 *   seus valores com uma chamada da função Min_Heapify.
 *
 * Entradas:
 *   (Heap*) heap: o heap mínimo do qual queremos extrair uma chave.
 * 
 * Saídas:
 *   (Vertice) min: vertice com o menor custo dentre aqueles do heap.
 */
Vertice Heap_Extract_Min(Heap* heap);

/**
 * Função: Heap_Decrease_Key
 *   Altera o valor de uma chave, substituindo o custo de um dado
 *   vertice por outro custo com um valor menor. Feita essa mudança,
 *   é necessário se atualizar o heap a fim de manter a propriedade 
 *   de um heap mínimo.
 * 
 * Entrada:
 *   (Heap*) heap: o heap cujo elemento queremos modificar.
 *   (int) i: o índice do elemento do heap a ser alterado.
 *   (Vertice) v: um vertice contendo os novos valores para a chave.
 */
void Heap_Decrease_Key(Heap* heap, int i, Vertice v);


#endif