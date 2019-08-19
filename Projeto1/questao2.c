#include <stdio.h>
#define MAX 10
 
void recebe_notas(float *notas, int *apr, int n){
    for(int i = 0; i < n; i++){
        if(*(notas + i) >= 6.0)
            *(apr + i) = 1;
        else
            *(apr + i) = 0;
    }
}

void conta_notas(int *apr, int n, int *aprov, int *reprov){
    for(int i = 0; i < n; i++){
        if(*(apr + i) == 1)
            *aprov+=1;
    }
    *reprov = n - *aprov;
}

int percent_aprov(int aprov, int reprov, float *perc_aprov, float *perc_reprov){
    float total = aprov + reprov;
    
    *perc_aprov = (aprov/total) * 100;
    *perc_reprov = (reprov/total) * 100;

    if(aprov > (total/2))
        return 1;
    else
        return 0;
}

int main(){

    float notas[MAX];
    int apr[MAX];
    float perc_aprov = 0, perc_reprov = 0;
    int aprov = 0, reprov = 0, n = MAX, metadeTurma;

    printf("----------------------------\n");
    printf("Sistema de controle de notas\n");
    printf("----------------------------\n\n");

    printf("Insira as notas\n");
    for(int i = 0; i < 10;i++){
        printf("Nota do aluno %d: ",(i+1));
        scanf("%f",(notas+i));
    }

    recebe_notas(notas, apr, n);
    conta_notas(apr, n, &aprov, &reprov);
    metadeTurma = percent_aprov(
        aprov, reprov, &perc_aprov, &perc_reprov);

    printf("\nResultados: \n");
    printf("\tQuantidade de aprovados: %d\n", aprov);
    printf("\tQuantidade de reprovados: %d\n", reprov);
    printf("\tPercentual de aprovados: %.1f %%\n", perc_aprov);
    printf("\tPercentual de reprovados: %.1f %%\n", perc_reprov);
    if(metadeTurma == 1){
        printf("\n\tMais da metade da turma aprovada.\n\n");
    }else{
        printf("\n\tMais da metade da turma não foi aprovada.\n\n");
    }

    return 0;
}
