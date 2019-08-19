#ifndef ILBP_H
#define ILBP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    void avanc_string(char *v);
    double get_area_pixel(int i, int j, int *matrix, int *area);
    void set_binary_matrix(int *area,int *binario, double sum);
    void transform_bin_caracol(char *bin_str,int *binario);
    int get_ilbp_numb(char *bin_str);
    void set_ilbp_number_vector(double *number_ilbp,int result_ilbp);
    double distancia_euclidiana(double *number_ilbp, double *number_ilbp_media);

#endif
