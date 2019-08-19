#include <stdio.h>
#include <stdlib.h>

int * recebe_notas(float * notas, int n)
{
    int *apr = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++)
    {
        if(*(notas + i) >= 6.0)
        {
            apr[i] = 1;
        }else{
            apr[i] = 0;
        }
    }
    return apr;
}
int * conta_notas(int * apr, int n)
{
    int *contador = calloc(2, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        if(*(apr + i) == 1){
            contador[0] += 1;
        }else{
            contador[1] += 1;
        }
    }
    return contador;
}


int percent_aprov(int * contador, float *perc_aprov, float *perc_reprov){
    float aprovados = contador[0];
    float reprovados = contador[1];
    int total = aprovados + reprovados;

    *perc_aprov = (aprovados/total) * 100;
    *perc_reprov = (reprovados/total) * 100;

    if(aprovados > (total/2))
        return 1;
    else
        return 0;
}

int main()
{
    int n = 10;
    float perc_aprov = 0, perc_reprov = 0;
    float notes[n];
    float *nts = notes;

    printf("----------------------------\n");
    printf("Sistema de controle de notas\n");
    printf("----------------------------\n\n");
    printf("Digite as 10 notas!\n\n");
    for(int i = 0; i < n; i++)
    {
        printf("Nota numero %d: ", (i+1));
        scanf("\n%f", &notes[i]);
    }
    int * apr = recebe_notas(nts, n);
    int * contador = conta_notas(apr, n);
    int metadeTurma = percent_aprov(contador, &perc_aprov, &perc_reprov);

    printf("\n");
    printf("----------------------------\n");
    printf("\t Resultados\n");
    printf("----------------------------\n\n");
    printf("Quantidade de aprovados: %d\n", contador[0]);
    printf("Quantidade de reprovados: %d\n", contador[1]);
    printf("Percentual de aprovados: %.1f %%\n", perc_aprov);
    printf("Percentual de reprovados: %.1f %%\n", perc_reprov);
    printf(metadeTurma ? "\nMais da metade da turma aprovada!\n" : "\tMais da metade da turma NÃO aprovada.");

    return 0;
}
