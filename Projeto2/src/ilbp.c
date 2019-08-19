#include "ilbp.h"
#include <math.h>

double get_area_pixel(int i, int j,int *matrix, int *area){
    int lin = 0, col = 0;
    double sum = 0;
    for(int a = i-1; a < i+2; a++){
        col = 0;
        for(int b = j-1; b < j+2;b++){
            *(area+(lin*3)+col) = *(matrix+(a*1026)+b);
            sum+= *(area+(lin*3)+col);
            col++;
        }
        lin++;
    }

    return sum;
}

void set_binary_matrix(int *area,int *binario, double sum){
    for(int a = 0; a < 3;a++){
        for(int b = 0; b < 3; b++){
            if(*(area+(a*3)+b) >= (sum/9))
                *(binario+(a*3)+b) = 1;
            else
                *(binario+(a*3)+b) = 0;
        }
    }
}

void transform_bin_caracol(char *bin_str,int *binario){
    *(bin_str + 0) = (char)(*(binario+(3*0)+0))+48;
    *(bin_str + 1) = (char)(*(binario+(3*0)+1))+48;
    *(bin_str + 2) = (char)(*(binario+(3*0)+2))+48;
    *(bin_str + 3) = (char)(*(binario+(3*1)+2))+48;
    *(bin_str + 4) = (char)(*(binario+(3*2)+2))+48;
    *(bin_str + 5) = (char)(*(binario+(3*2)+1))+48;
    *(bin_str + 6) = (char)(*(binario+(3*2)+0))+48;
    *(bin_str + 7) = (char)(*(binario+(3*1)+0))+48;
    *(bin_str + 8) = (char)(*(binario+(3*1)+1))+48;
}

int get_ilbp_numb(char *bin_str){
    int result_ilbp = (int) strtol(bin_str, NULL, 2);
    for(int a = 0; a < 8;a++){
        avanc_string(bin_str);

        if((int) strtol(bin_str, NULL, 2) < result_ilbp)
            result_ilbp = (int) strtol(bin_str, NULL, 2);

    }
    return result_ilbp;
}

void set_ilbp_number_vector(double *number_ilbp,int result_ilbp){
    *(number_ilbp+result_ilbp) = *(number_ilbp+result_ilbp) + 1;
}

void avanc_string(char *v){
    char *ptr = v;
    char *temp = malloc(9*sizeof(char));

    temp[0] = ptr[8];

    for(int i = 1; i < 9; i++){
        temp[i] = ptr[i-1];
    }
    for(int i = 0; i < 9; i++){
        *(v+i) = *(temp+i);
    }
    free(temp);
}

double distancia_euclidiana(double *number_ilbp, double *number_ilbp_media){
    double sum = 0.0;

    for(int i = 0; i < 512;i++){
        double dif = number_ilbp_media[i] - number_ilbp[i];
        sum += pow(dif,2);
    }

    double dist = sqrt(sum);

    return dist;
}
