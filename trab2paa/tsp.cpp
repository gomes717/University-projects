/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém a função main do segundo trabalho elaborado para a
 *   disciplina de Projeto e Análise de Algoritmos do curso de
 *   Engenharia de Computação da UTFPR.
 */

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<chrono>

#include "structs.h"
#include "principais.h"
#include "auxiliares.h"
#include "heap.h"

using namespace std::chrono;

//============================================================//
//--------------------------- MAIN ---------------------------//
//============================================================//

int main(int argc, char* argv[])
{
    //Tomada de tempo inicial
    high_resolution_clock::time_point start = high_resolution_clock::now();

    //Abrir arquivo de entrada
    char* filename;  

    if (argc != 2)
	{
		fprintf(stderr, "Uso: %s testing\n", argv[0]);
		return 1;
	}
    filename = argv[1];  

    /*--------------------------------------------------*/
    /* Retirar dados do arquivo */
    
    FILE* fp;
             
    int n;  //número de pontos
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Falha ao ler arquivo.\n");
        return 1;
    }
     
    fscanf(fp, "%d", &n);

    /* Alocar e copiar memória */    
    Point* pts = (Point*)malloc(sizeof(Point)*(n));

    // O índice de cada ponto no vetor de pontos atua como uma espécie
    // de identificador universal para o ponto, sendo usado para iden-
    // tificá-lo individualmente através de todo o algoritmo.
    for(int i = 0; i<n; i++)
    {
        fscanf(fp, "%d", &pts[i].x);
        fscanf(fp, "%d", &pts[i].y);
    }

    fclose(fp);

    /*------------------------------------------------*/
    /* Executar o algoritmo para os pontos dados */

    //Gerar grafo completo à partir dos pontos
    float** graphMat = gen_graph_mat(n, pts);

    //AGM retorna um vetor com os vertices, e o vertice 
    //mostra quem são o pai e o index dele
    Vertice* vertice_arr = AGM_Prim(graphMat, n, 0);

    //Desalocar a memória do graphMat
    for(int i = 0; i < n;i++)
        free(graphMat[i]);
    free(graphMat);

    //Exportar as arestas da AGM para o arquivo tree.txt
    FILE* f_tree = fopen("tree.txt", "w");
    if (f_tree == NULL)
    {
        fprintf(stderr, "Falha ao escrever no arquivo.\n");
        return 1;
    } 

    for(int i = 0;i<n-1;i++)
    {
        fprintf(f_tree, "%d %d\n%d %d\n"    , pts[vertice_arr[i].pai].x
                                            , pts[vertice_arr[i].pai].y
                                            , pts[vertice_arr[i].index].x
                                            , pts[vertice_arr[i].index].y);
    }
    fclose(f_tree);

    //Transforma as arestas da AGM em um grafo em lista de adjacências para a busca
    Elemento* graphList = gen_graph_list(n, vertice_arr, pts);

    //Desalocar a memória do vertice_arr
    free(vertice_arr);

    //Utilizamos um vetor de tamanho n+1 para guardar o ciclo da busca em profundidade
    int* cycle = (int*) malloc (sizeof(int)*(n+1));
    int cycle_idx = 0;

    busca_profundidade(graphList,0,cycle, &cycle_idx);
    cycle[n] = 0;

    //Exportar o ciclo para o arquivo cycle.txt e calcular o custo total do ciclo
    FILE* f_cycle = fopen("cycle.txt", "w");
    if (f_cycle == NULL)
    {
        fprintf(stderr, "Falha ao escrever no arquivo.\n");
        return 1;
    } 

    float cycle_cost = 0;   
    for(int i=0; i<n; i++)
    {
        fprintf(f_cycle,"%d %d\n", pts[cycle[i]].x,pts[cycle[i]].y);
        cycle_cost += dist(pts[cycle[i]], pts[cycle[i+1]]);
    }
    fprintf(f_cycle,"%d %d\n", pts[0].x,pts[0].y);
    fclose(f_cycle);

    //Limpeza das alocações dinamicas
    free(cycle);
    for(int i=0;i<n;i++){
        Elemento* aux = graphList[i].prox;
        while(aux != NULL)
        {
            Elemento* aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
    }
    free(graphList);
    
    //Tomada de tempo final
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> time = duration_cast<duration<double>>(end - start);

    printf("%.6f %.6f", time.count(), cycle_cost);
    
    return 0;
}