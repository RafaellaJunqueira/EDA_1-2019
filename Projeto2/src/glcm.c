#include "glcm.h"
#include <string.h>
#include <math.h>
#define GMAX 256
#define GRESULT 24

int *set_vector(FILE *f, int tam, int top, int *vec){
    char *c, var[1], comp[0];
    char num[top];
    int bot = 1, i = 0, j = 0, pix;
    int *matrix = (int*) malloc(1026*1026*sizeof(int));

    f = fopen("grass_01.txt", "r");

    while(!feof(f)){
        for(int i = 0;i < 1025; i++){
            for(int j = 0; j < 1025; j++){
                fscanf(f,"%d%c",(matrix+(i*1026)+j),&c);
            }
        }
    }
    fclose(f);
    return vec;
}

void delete_matrix(int **m){
    free(m);
}
void g_Right(int **image, double *result){

	int i, j, **glcm_right;
	glcm_right = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_right[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if (j != GMAX){
				glcm_right[image[i][j]][image[i][j + 1]]++;
			}
		}
	}
	g_Contrast(glcm_right, result);
	g_Energy(glcm_right, result);
	g_Homogeneity(glcm_right, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_right[i]);
	}

	free(glcm_right);
}

void g_Left(int **image, double *result){
	int i, j, **glcm_left;
	glcm_left = (int **)calloc(GMAX, sizeof(int *));
	for (i = 0; i < GMAX; i++){
		glcm_left[i] = (int *)calloc(GMAX, sizeof(int));
	}
	for (i = 0; i < GMAX; i++){
		for (j = 0; j <GMAX; j++){
			if (j != 0){
				glcm_left[image[i][j]][image[i][j - 1]]++;
			}
		}
	}
	g_Contrast(glcm_left, result);
	g_Energy(glcm_left, result);
	g_Homogeneity(glcm_left, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_left[i]);
	}

	free(glcm_left);
}

void g_Upper(int **image, double *result){

	int i, j, **glcm_upper;
	glcm_upper = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_upper[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if (i != 0){
			glcm_upper[image[i - 1][j]][image[i][j]]++;
			}
		}
	}
	g_Contrast(glcm_upper, result);
	g_Energy(glcm_upper, result);
	g_Homogeneity(glcm_upper, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_upper[i]);
	}

	free(glcm_upper);
}

void g_Bottom(int **image, double *result){

	int i, j, **glcm_bottom;
	glcm_bottom = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_bottom[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if (i != GMAX){
				glcm_bottom[image[i + 1][j]][image[i][j]]++;
			}
		}
	}
	g_Contrast(glcm_bottom, result);
	g_Energy(glcm_bottom, result);
	g_Homogeneity(glcm_bottom, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_bottom[i]);
	}

	free(glcm_bottom);
}

void g_UpperRight(int **image, double *result){

	int i, j, **glcm_upper_right;

	glcm_upper_right = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_upper_right[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if ((i != 0) && (j != GMAX)){
				glcm_upper_right[image[i - 1][j]][image[i][j + 1]]++;
			}
		}
	}
	g_Contrast(glcm_upper_right, result);
	g_Energy(glcm_upper_right, result);
	g_Homogeneity(glcm_upper_right, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_upper_right[i]);
	}

	free(glcm_upper_right);
}

void g_UpperLeft(int **image, double *result){

	int i, j, **glcm_upper_left;

	glcm_upper_left = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_upper_left[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if ((i != 0) && (j != 0)){
				glcm_upper_left[image[i - 1][j]][image[i][j - 1]]++;
			}
		}
	}

	g_Contrast(glcm_upper_left, result);
	g_Energy(glcm_upper_left, result);
	g_Homogeneity(glcm_upper_left, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_upper_left[i]);
	}

	free(glcm_upper_left);
}

void g_BottomLeft(int **image, double *result){

	int i, j, **glcm_bottom_left;

	glcm_bottom_left = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_bottom_left[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if ((i != GMAX) && (j != 0)){
				glcm_bottom_left[image[i + 1][j]][image[i][j - 1]]++;
			}
		}
	}
	g_Contrast(glcm_bottom_left, result);
	g_Energy(glcm_bottom_left, result);
	g_Homogeneity(glcm_bottom_left, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_bottom_left[i]);
	}

	free(glcm_bottom_left);
}

void g_BottomRight(int **image, double *result){

	int i, j, **glcm_bottom_right;

	glcm_bottom_right = (int **)calloc(GMAX, sizeof(int *));

	for (i = 0; i < GMAX; i++){
		glcm_bottom_right[i] = (int *)calloc(GMAX, sizeof(int));
	}

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if ((i != GMAX) && (j != GMAX)){
				glcm_bottom_right[image[i + 1][j]][image[i][j + 1]]++;
			}
		}
    }
	g_Contrast(glcm_bottom_right, result);
	g_Energy(glcm_bottom_right, result);
	g_Homogeneity(glcm_bottom_right, result);

	for (i = 0; i < GMAX; i++){
		free(glcm_bottom_right[i]);
	}

	free(glcm_bottom_right);
}
void g_Homogeneity(int **glcm, double *result){

	int i, j;
	double aux = 0, homog = 0;

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			if ((i - j) != -1){
				aux = ((double)glcm[i][j] / (double)(1 + (i - j)));
				homog += aux;
			}
		}
	}

	for (i = 0; i < GRESULT; i++){
		if (result[i] == 0){
			result[i] = homog;
			break;
		}
	}
}

void g_Contrast(int **glcm, double *result){

	int i, j;
	double contrast = 0;

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			contrast += ((i - j) * (i - j)) * glcm[i][j];
		}
	}
	for (i = 0; i < GRESULT; i++){
		if (result[i] == 0){
			result[i] = contrast;
			break;
		}
	}
}

void g_Energy(int **glcm, double *result){
	int i, j;
	double energy = 0;

	for (i = 0; i < GMAX; i++){
		for (j = 0; j < GMAX; j++){
			energy += (glcm[i][j] * glcm[i][j]);
		}
	}

	for (i = 0; i < GRESULT; i++){
		if (result[i] == 0){
			result[i] = energy;
			break;
		}
	}
}


void glcm(int **image, double *result){
    g_Right(image, result);
    g_Left(image, result);
    g_Upper(image, result);
    g_Bottom(image, result);
    g_UpperRight(image, result);
    g_UpperLeft(image, result);
    g_BottomLeft(image, result);
    g_BottomRight(image, result);
}
