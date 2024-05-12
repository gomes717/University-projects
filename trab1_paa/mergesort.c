#include "structs.h"
#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>


void mergesort(Points* vec, int start, int end, int axis)
{
	//printf("entrou: %d %d\n", start, end);
	if (start < end)
	{
		int mid =  (end + start) / 2;
		mergesort(vec, start, mid, axis);
		mergesort(vec, mid + 1, end, axis);
		merge(vec, start, mid, end, axis);
	}
}


void merge(Points* vec, int start,  int mid,  int end, int axis)
{
	int n1 = mid - start + 1;
	int n2 = end - mid;

	Points *L , *R;
	L = (Points*)malloc(n1 * sizeof(Points));
	R = (Points*)malloc(n2 * sizeof(Points));
	for (int i = 0; i < n1; i++)
	{
		L[i].x = vec[start + i].x;
        L[i].y= vec[start + i].y;
	}
	for (int j = 0; j < n2; j++)
	{
		R[j].x = vec[mid + 1 + j].x;
        R[j].y = vec[mid + 1 + j].y;
	}

	int i = 0, j = 0, k = start;
	while (i < n1 && j < n2)
	{
		if(axis == X_AXIS)
		{
			if (L[i].x <= R[j].x)
			{
				vec[k] = L[i];
				i++;
			}
			else
			{
				vec[k] = R[j];
				j++;
			}
			k++;
		}
		else if(axis == Y_AXIS)
		{
			if (L[i].y <= R[j].y)
			{
				vec[k] = L[i];
				i++;
			}
			else
			{
				vec[k] = R[j];
				j++;
			}
			k++;

		}
		
	}
	
	while (j < n2)
	{
		vec[k] = R[j];
		j++;
		k++;
	}

	while (i < n1)
	{
		vec[k] = L[i];
		i++;
		k++;
	}
	

	free(L);
	free(R);
}

