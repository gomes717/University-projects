/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém a implementação das funções auxiliares utilizadas.
 */

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "auxiliares.h"

//============================================================//
//-------------------- FUNÇÕES AUXILIARES --------------------//
//============================================================//

#define PI 3.14159265

float dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

void order_vertice_arr(const int n, Vertice* vertice_arr, Point* pts)
{
    double* angulo_arr = (double*)malloc(sizeof(double)*(n-1));
    Point zero_coordenada = { 0, 0 };
    for(int i = 0;i<n-1; i++)
    {   
        //calculos malucos que eu pensei para fazer isso
        float d_filho = dist(pts[vertice_arr[i].index], zero_coordenada);
        float d_pai = dist(pts[vertice_arr[i].pai], zero_coordenada);
        float d_pai_filho = dist(pts[vertice_arr[i].index], pts[vertice_arr[i].pai]);
        
        double alfa_filho;
        if(pts[vertice_arr[i].index].x != 0)
            alfa_filho = atan(pts[vertice_arr[i].index].y/pts[vertice_arr[i].index].x);
        else if(d_filho == 0)
            alfa_filho = 0;
        else
            alfa_filho = PI;

        double alfa_pai;
        if(pts[vertice_arr[i].pai].x != 0)
            alfa_pai = atan(pts[vertice_arr[i].pai].y/pts[vertice_arr[i].pai].x);
        else if(d_pai == 0)
            alfa_pai = 0;
        else
            alfa_pai = PI;
        //lei dos cossenos para encontrar o angulo
        double beta = acos((-1)*(pow(d_filho,2) - pow(d_pai,2) - pow(d_pai_filho,2))/(2*d_pai*d_pai_filho));
        if(alfa_filho > alfa_pai)
            beta = 2*PI - beta;
        angulo_arr[i] = beta;
    }
    mergesort(angulo_arr, vertice_arr, 0, n-2);
    free(angulo_arr);
}

Elemento* gen_graph_list(const int n, Vertice* vertice_arr, Point* pts)
{
    order_vertice_arr(n, vertice_arr, pts);
    Elemento* graphList = (Elemento*)malloc(sizeof(Elemento)*n);
    for(int i = 0; i<n; i++)
    {
        graphList[i].index = i;
        graphList[i].prox = NULL;
        graphList[i].visitado = false;
    }
    
    for(int i = 0; i<n-1; i++)
    {
        Elemento* new_ele = (Elemento*)malloc(sizeof(Elemento));
        int pai = vertice_arr[i].pai;
        new_ele->index = vertice_arr[i].index;
        new_ele->prox = NULL;
        new_ele->visitado = false;

        if(graphList[pai].prox != NULL)
            new_ele->prox = graphList[pai].prox;        
        graphList[pai].prox = new_ele;

    }

    return graphList;
}

void print_graph_list(const int n, Elemento* graphList)
{
    for(int i = 0;i < n; i++){
        if(graphList != NULL){
            Elemento* aux = &graphList[i];
            //printf("%d\n",graphList[i].primeiro->index);
            printf("%d, ",i);
            while(aux != NULL)
            {
                printf("%d\t",aux->index);
                aux = aux->prox;
                //printf("%d\n",aux->index);
            }
            printf("\n");
        }
        else
        {
            printf("%d, nao possui filho\n",i);
        }
    }
}
