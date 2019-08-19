#include "neurais.h"

int *sorteio_teste_treino()
{
    srand(time(NULL));
    int *n = (int *)malloc(50 * sizeof(int));

    int x = 1, y = 0;
    n[0] = rand() % 50 + 1;

    while(x < 50)
    {
        n[x] = rand() % 50 + 1;
        y = 0;

        while(y < x)
        {
            if (n[y] == n[x])
            {
                --x;
                break;
            }
            ++y;
        }
        ++x;
    }
    return n;
}
int salva_arquivos(int *vetor, int teste_treino, int grama_asfalto)
{
    char nome[20];
    char diretorio[256];
    int i = 0;
    int tipo;

    if(teste_treino == 0 && grama_asfalto == 0)
    {
        strcpy(nome, "teste_grass.txt");
        strcpy(diretorio, "DataSet/grass/grass_");
        tipo = 0;
    }
    else if(teste_treino == 0 && grama_asfalto == 1)
    {
        strcpy(nome, "teste_asphalt.txt");
        strcpy(diretorio, "DataSet/asphalt/asphalt_");
        tipo = 1;
    }
    else if(teste_treino == 1 && grama_asfalto == 0)
    {
        strcpy(nome, "treino_grass.txt");
        strcpy(diretorio, "DataSet/grass/grass_");
        tipo = 2;
    }
    else if(teste_treino == 1 && grama_asfalto == 1)
    {
        strcpy(nome, "treino_asphalt.txt");
        strcpy(diretorio, "DataSet/asphalt/asphalt_");
        tipo = 3;
    }
    else
    {
        printf("ERRO");
    }
    FILE *arquivo = NULL;
    arquivo = fopen(nome, "wt");

    int aux;
    char temp[50];

    for (i = 0; i < 25; i++)
    {
        if (vetor[i] < 10)
        {
            aux = sprintf(temp, "%s0%d.txt\n", diretorio, vetor[i]);
            fprintf(arquivo, "%s", temp);
        }
        else if (vetor[i] >= 10)
        {
            aux = sprintf(temp, "%s%d.txt\n", diretorio, vetor[i]);
            fprintf(arquivo, "%s", temp);
        }
    }
    fclose(arquivo);
    return tipo;
}
