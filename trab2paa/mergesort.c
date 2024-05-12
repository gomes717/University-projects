/** 
 * Autores:
 *   Guilherme Gomes Barboza - RA: 2022567
 *   Gustavo Valente Gulmine - RA: 2026953 
 * 
 * Descrição:
 *   Contém as implementações das funções utilizadas para o Mergesort.
 */

//============================================================//
//------------------------- INCLUDES -------------------------//
//============================================================//

#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>

//============================================================//
//------------------------ MERGESORT -------------------------//
//============================================================//

void mergesort(double* angulo_arr, Vertice*  vertice_arr, int start, int end)
{
	//printf("entrou: %d %d\n", start, end);
	if (start < end)
	{
		int mid =  (end + start) / 2;
		mergesort(angulo_arr,vertice_arr, start, mid);
		mergesort(angulo_arr,vertice_arr, mid + 1, end);
		merge(angulo_arr,vertice_arr, start, mid, end);
	}
}


void merge(double* angulo_arr,Vertice*  vertice_arr, int start,  int mid,  int end)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;

	double *L_angulo , *R_angulo;
	L_angulo = (double*)malloc(n1 * sizeof(double));
	R_angulo = (double*)malloc(n2 * sizeof(double));
	Vertice *L_vertice, *R_vertice;
	L_vertice = (Vertice*)malloc(n1 * sizeof(Vertice));
	R_vertice = (Vertice*)malloc(n2 * sizeof(Vertice));
	for (int i = 0; i < n1; i++)
	{
		L_angulo[i] = angulo_arr[start + i];
        L_vertice[i]= vertice_arr[start + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R_angulo[j] = angulo_arr[mid + 1 + j];
        R_vertice[j] = vertice_arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = start;
	while (i < n1 && j < n2)
	{
			if (L_angulo[i] >= R_angulo[j])
			{
				angulo_arr[k] = L_angulo[i];
				vertice_arr[k] = L_vertice[i];
				i++;
			}
			else
			{
				angulo_arr[k] = R_angulo[j];
				vertice_arr[k] = R_vertice[j];
				j++;
			}
			k++;
		}
	
	while (j < n2)
	{
		angulo_arr[k] = R_angulo[j];
		vertice_arr[k] = R_vertice[j];
		j++;
		k++;
	}

	while (i < n1)
	{
		angulo_arr[k] = L_angulo[i];
		vertice_arr[k] = L_vertice[i];
		i++;
		k++;
	}
	

	free(L_angulo);
	free(R_angulo);
	free(L_vertice);
	free(R_vertice);
}

