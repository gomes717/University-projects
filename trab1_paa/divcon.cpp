#include<math.h>
#include<vector>

#include "structs.h"
#include "divcon.h"
#include "bruteforce.h"

using namespace std;

double min(double a, double b)
{
    if(a<=b)
        return a;
    else
        return b;   
}

Points* divConDist(Points* ptsx, Points* ptsy, int start, int end)
{
    static Points pts_r[2];

    //Caso base       
    if(end-start > 0 && end-start < 3) // 3 elementos ou menos
    {
        double d1 = dist(ptsx[start], ptsx[end]); // 1o e 3o ou 1o e 2o
        double d2 = dist(ptsx[start], ptsx[start+1]); // 1o e 2o 
        double d3 = dist(ptsx[end-1], ptsx[end]); // 2o e 3o ou 1o e 2o

        double menor = min(d1, min(d2, d3));

        if(menor == d1)
        {
            pts_r[0] = ptsx[start];
            pts_r[1] = ptsx[end];
            return pts_r;
        }
        else if(menor == d2)
        {
            pts_r[0] = ptsx[start];
            pts_r[1] = ptsx[start+1];
            return pts_r;
        }
        else
        {
            pts_r[0] = ptsx[end-1];
            pts_r[1] = ptsx[end];
            return pts_r;
        }
        
    }

    //Caso iterativo
    int mid = floor((start + end)/2);
    double median_x = ptsx[mid].x;

    Points* left = divConDist(ptsx, ptsy, start, mid); //Pontos da menor distância para X<=mediana
    Points* right = divConDist(ptsx, ptsy, mid + 1, end); //Pontos da menor distância para X>mediana

    double dl = dist(left[0], left[1]); //Menor distância p/ X<=mediana
    double dr = dist(right[0], right[1]); //Menor distância p/ X>mediana

    //Define delta como a menor distância
    double delta = min(dl, dr);
    double mindist = delta;
    if(dl<dr)
    {
        pts_r[0] = left[0];
        pts_r[1] = left[1];
    }
    else
    {
        pts_r[0] = right[0];
        pts_r[1] = right[1];
    }
    
    //Percorre o vetor ordenado em Y e cria um vector com os pontos cujo X pertençe ao recorte
    int n_slab = 0;
    int i,j;
    double aux;
    vector<Points> slab;

    for(i = start; i<=end; i++)
    {
        aux = ptsy[i].x;
        if(aux < (median_x+delta) || aux > (median_x-delta)) //Se o atual ponto pertence ao recorte
        {
            slab.push_back(ptsy[i]); //Adiciona o ponto ao final, mantendo a ordenação em Y de ptsy
            n_slab++;
        }
    }

    for(i = 0; i<n_slab; i++)
    {
        j=1;
        while(j<7 && (i+j)<n_slab) //Só é necessário verificar 6 outros pontos para cada ponto no recorte
        {
            aux = dist(slab.at(i), slab.at(i+j));
            if(aux<mindist)
            {
                mindist = aux;
                pts_r[0] = slab.at(i);
                pts_r[1] = slab.at(i+j);
            }
            j++;
        }
    }
    
    return pts_r;
}