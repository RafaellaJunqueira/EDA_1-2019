#ifndef GLCM_H
#define GLCM_H
#include <stdlib.h>
#include <stdio.h>

int *set_vector(FILE *f, int tam, int top, int *vec);
void delete_matrix(int **m);
//separacao por funcoes de cada direcao do algoritmo
void g_Right(int **image, double *result);
void g_Left(int **image, double *result);
void g_Upper(int **image, double *result);
void g_Bottom(int **image, double *result);
void g_UpperRight(int **image, double *result);
void g_UpperLeft(int **image, double *result);
void g_BottomLeft(int **image, double *result);
void g_BottomRight(int **image, double *result);
void g_Energy(int **image, double *result);
void g_Homogeneity(int **image, double *result);
void g_Contrast(int **image, double *result);
void glcm(int **image, double *result);

#endif
