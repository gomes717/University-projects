/*======================================================*/
/* HEADER FILES */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<string>
#include <chrono>

#include "structs.h"
#include "mergesort.h"
#include "bruteforce.h"
#include "divcon.h"


using namespace std;
using namespace std::chrono;

/*======================================================*/
/* AUXILIARY FUNCTIONS & STRUCT DEFINITIONS */

/*======================================================*/

int main(int argc, char *argv[])
{
    /*--------------------------------------------------*/
    /* Retrieve filename */
    string s1;  

    if (argc != 2)
	{
		fprintf(stderr, "Uso: %s testing\n", argv[0]);
		return 1;
	}

    s1 = argv[1];
    //s1.insert(0, "./");
    char* filename = new char[s1.length()+1];
    strcpy(filename, s1.c_str());    

    /*--------------------------------------------------*/
    /* Retrieve data from file */
    FILE* fp;
    Points* ptsx = NULL; //Entry points that will be sorted by X axis values
    Points* ptsy = NULL; //Entry points that will be sorted by Y axis values
    int n;  
    
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Falha ao ler arquivo.\n");
        return 1;
    }
     
    fscanf(fp, "%d", &n);
    printf("%d\n", n);

    /* Allocate and copy memory */
    ptsx = (Points*)malloc(sizeof(Points)*(n));
    ptsy = (Points*)malloc(sizeof(Points)*(n));
    
    for(int i = 0; i<n; i++)
    {
        fscanf(fp, "%lf", &ptsx[i].x);
        fscanf(fp, "%lf", &ptsx[i].y);
        ptsy[i] = ptsx[i];
    }

    fclose(fp);

    /* Sort the arrays */
    mergesort(ptsx, 0, n-1, X_AXIS);
    mergesort(ptsy, 0, n-1, Y_AXIS);

    /*--------------------------------------------------*/
    /* Brute Force */

    high_resolution_clock::time_point start_bf = high_resolution_clock::now();
    Points* resultado = bruteForceDist(ptsx,n);
    high_resolution_clock::time_point end_bf = high_resolution_clock::now();
    duration<double> diff_time_bf = duration_cast<duration<double>>(end_bf - start_bf);
    

    /*--------------------------------------------------*/
    /* Divide and Conquer */

    high_resolution_clock::time_point start_dc = high_resolution_clock::now();
    Points* resultadoD = divConDist(ptsx, ptsy, 0, n-1);
    high_resolution_clock::time_point end_dc = high_resolution_clock::now();
    duration<double> diff_time_dc = duration_cast<duration<double>>(end_dc - start_dc);

    /*--------------------------------------------------*/
    /* Output file */

    FILE *fo = fopen("output.txt", "a");

	if(fo == NULL)
    {
        fprintf(stderr, "Falha ao criar output.txt.\n");
        return 1;
    }

    //fbt fbd fbx1 fby1 fbx2 fby2 dct dcd dcx1 dcy1 dcx2 dcy2
    fprintf(fo,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n"
            , diff_time_bf
            , dist(resultado[0], resultado[1])
            , resultado[0].x
            , resultado[0].y
            , resultado[1].x
            , resultado[1].y
            , diff_time_dc
            , dist(resultadoD[0], resultadoD[1])
            , resultadoD[0].x
            , resultadoD[0].y
            , resultadoD[1].x
            , resultadoD[1].y
            );
    fclose(fo);
    /*--------------------------------------------------*/

    free(ptsx);
    free(ptsy);
    return 0;
}

