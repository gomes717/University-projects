/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as implementações das funções
 *   atreladas ao uso do Heap. 
 */

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "heap.h"
#include <stdio.h>

//============================================================//
//--------------------------- HEAP ---------------------------//
//============================================================//

int Parent(int i) { return (int)(i/2); }

int Left(int i) 
{ 
    if(i == 0)    
        return 2;
    return 2*i; 
}

int Right(int i) 
{ 
    if(i == 0)    
        return 1;
    return 2*i + 1; 
}

void Min_Heapify(Heap* heap, int i)
{
    int l = Left(i);
    int r = Right(i);
    int menor = i;
    if(l <= heap->tamanho_heap && heap->array[i].custo > heap->array[l].custo)
        menor = l;
    if(r <= heap->tamanho_heap && heap->array[menor].custo > heap->array[r].custo)
        menor = r;
    if(menor != i)
    {
        Vertice aux = heap->array[i];
        heap->array[i] = heap->array[menor];
        heap->array[menor] = aux; 
        Min_Heapify(heap,menor);
    }
}

Heap Build_Min_Heap(Vertice* array, int n)
{
    static Heap heap;
    heap.comprimento = n -1;
    heap.tamanho_heap = n - 1;
    heap.array = array;
    for(int i = (int)(n/2);i >= 0;i--)
        Min_Heapify(&heap, i);
    return heap;
}

Vertice Heap_Extract_Min(Heap* heap)
{
    if(heap->tamanho_heap < 0)
    {
        printf("Erro heap vazio\n");
        Vertice vazio = {-1, -1, -1};
        return vazio;
    }
    Vertice min = heap->array[0];
    heap->array[0] = heap->array[heap->tamanho_heap];
    heap->array[heap->tamanho_heap] = min;
    heap->tamanho_heap--;
    Min_Heapify(heap,0);
    return min;
}

void Heap_Decrease_Key(Heap* heap,int i ,Vertice v)
{
    heap->array[i].custo = v.custo;
    while(i > 0 && heap->array[Parent(i)].custo > heap->array[i].custo)
    {
        Vertice aux = heap->array[Parent(i)];
        heap->array[Parent(i)] = heap->array[i];
        heap->array[i] = aux;
        i = Parent(i);
    }
}