/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as definições das funções utilizadas para o Mergesort.
 */

#ifndef __MERGESORT__
#define __MERGESORT__

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "structs.h"

//============================================================//
//------------------------ MERGESORT -------------------------//
//============================================================//

/**
 * Função: merge
 *   Ordena uma região dividida em duas partes de um vetor 
 *   baseado nos valores da mesma região do outro vetor.
 * 
 * Entradas: 
 *   (double*) ang_array: vetor dos angulos entre o pai e o filho
 *                        em relação ao ponto (0,0).
 *   (Vertice*)  vertice_arr: vetor dos vertices.
 *   (int) start: índice que marca o inicio da região a ser ordenada.
 *   (int) mid: índice que marca o meio da região a ser ordenada.
 *   (int) end: índice que marca o fim da região a ser ordenada.
 */
void merge(double* ang_array,Vertice*  vertice_arr, int start,  int mid,  int end);

/**
 * Função: mergesort
 *   Divide as regiões em 2 até chegar no caso base e então chama
 *   a função Merge para ordenar essas regiões até que o vetor
 *   seja totalmente ordenado.
 * 
 * Entradas:
 *   (double*) ang_array: vetor dos angulos entre o pai e o filho 
 *                        em relação ao ponto (0,0).
 *   (Vertice*) vertice_arr: vetor dos vertices.
 *   (int) start: índice que marca o inicio da região a ser ordenada.
 *   (int) end: índice que marca o fim da região a ser ordenada.
 *
 */
void mergesort(double* ang_array,Vertice*  vertice_arr, int start, int end);

#endif 