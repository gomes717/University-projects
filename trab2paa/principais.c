/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as implementações das funções principais desenvolvidas.
 */

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "principais.h"

//============================================================//
//-------------------- FUNÇÕES PRINCIPAIS --------------------//
//============================================================//

float** gen_graph_mat(const int n, Point* pts)
{
    float** graphMat = (float**)malloc(sizeof(float*)*n);
    for(int i = 0; i < n;i++)
        graphMat[i] = (float*)malloc(sizeof(float)*n); 

    for(int i = 0; i < n; i++){
        for(int j = i+1; j<n;j++)
        {
            graphMat[i][j] = sqrt(pow(pts[i].x - pts[j].x,2) + pow(pts[i].y - pts[j].y,2));
            graphMat[j][i] = graphMat[i][j];
        }
        graphMat[i][i] = 0;
    }

    return graphMat;
}

Vertice* AGM_Prim(float** graph_mat,const int n, int index)
{
    Vertice* vertice_arr = (Vertice*)malloc(sizeof(Vertice)*n);
    int i = 0;
    //cria um vetor de vertices inicial
    
    while(i < n)
    {
        vertice_arr[i].custo = FLT_MAX ;
        vertice_arr[i].pai = -1;
        vertice_arr[i].index = i;
        i++;
        //printf("%d,%e ",i-1, vertice_arr[i-1].custo);
    }
    //printf("\n");
    //inicializa o vertice que vai começar a AGM
    vertice_arr[index].custo = 0;
    //Constroi o Heap baseado no vetor inicializado
    Heap heap = Build_Min_Heap(vertice_arr, n);
    //Nesse while é criado a AGM
    while (heap.tamanho_heap > 0)
    {
        Vertice u = Heap_Extract_Min(&heap);
        i = u.index;
        //verifica u com todos os vertices v que ainda estão no heap
        for(int j = 0; j < heap.tamanho_heap + 1;j++)
        {
            if(heap.array[j].custo > graph_mat[i][heap.array[j].index] 
                && i != heap.array[j].index)
            {
                heap.array[j].custo = graph_mat[i][heap.array[j].index];
                heap.array[j].pai = i;
                Heap_Decrease_Key(&heap, j, heap.array[j]);
            }
        }
    }

    return vertice_arr;
}

void busca_profundidade(Elemento* graphList,int index, int* cycle, int* cycle_idx)
{
    graphList[index].visitado = true;
    cycle[*cycle_idx] = index;
    (*cycle_idx)++;

    Elemento* aux = &graphList[index];
    while(aux->prox != NULL)
    {
        aux = aux->prox;
        if(!aux->visitado)
            busca_profundidade(graphList,aux->index,cycle,cycle_idx);
    }
    
}
