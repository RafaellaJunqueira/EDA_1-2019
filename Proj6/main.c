<<<<<<< HEAD
#include "neurais.h"


int main()
{
    int nums_treino_asfalto[25] = {0};
    int nums_teste_asfalto[25] = {0};
    int nums_treino_grama[25] = {0};
    int nums_gra_teste[25] = {0};

    int *ordem_imagem_asfalto = sorteio_teste_treino();
    int *ordem_imagem_grama = sorteio_teste_treino();

    // Sorteia e salva arquivos de teinamento
    for(int i = 0; i < 25; ++i)
    {
        nums_treino_asfalto[i] = *(ordem_imagem_asfalto + i);
        nums_treino_grama[i] = *(ordem_imagem_grama + i);
    }
    int nomes_treino_grama = salva_arquivos(nums_treino_grama, 1, 0);
    int nomes_treino_asfalto = salva_arquivos(nums_treino_asfalto, 1, 1);

    // Sorteia e salva arquivos de teste
    for(int i = 0; i < 50; ++i)
    {
        nums_teste_asfalto[i - 25] = *(ordem_imagem_asfalto + i);
        nums_gra_teste[i - 25] = *(ordem_imagem_grama + i);
    }
    int nomes_teste_grama = salva_arquivos(nums_gra_teste, 0, 0);
    int nomes_teste_asfalto = salva_arquivos(nums_teste_asfalto, 0, 1);

//
// Treinamento GRAMA
//

    FILE *arquivo_treino_grama = fopen("treino_grass.txt", "r");
    char caminho_treino_grama[27];
    //
    // for(int i = 0; i < 25; i++)
    // {
        int **imagem_grama = (int **)malloc(1026 * sizeof(int *));
        for(int i = 0; i < 1026; i++)
        {
            imagem_grama[i] = (int *)malloc(1026 * sizeof(int));
        }

        fscanf(arquivo_treino_grama,"%s", caminho_treino_grama);
        FILE *file_grama = fopen(caminho_treino_grama, "r");

        printf("OK\n");
        // Salva a imagem lida
        for(int i = 0; i < 1025; i++)
        {
            for(int j = 0; j < 1025; j++)
                fscanf(file_grama, "%d%*c", &imagem_grama[i][j]);
        }


        // CONTINUAR COM O NECESSÁRIO PRA CADA IMAGEM DE TREINAMENTO DE GRAMA


        // for(int i = 0; i < 1025; i++)
        // {
        //     free(imagem_grama[i]);
        // }
        // free(imagem_grama);
        // fclose(file_grama);
    // }
    //
    fclose(arquivo_treino_grama);
//
// //
// // Treinamento ASFALTO
// //
//
//     FILE *arquivo_treino_asfalto = fopen("treino_asphalt.txt", "r");
//     char caminho_treino_asfalto[31];
//
//     for(int i = 0; i < 25; i++)
//     {
//         int **imagem_asfalto = (int **)malloc(1026 * sizeof(int *));
//         for(int i = 0; i < 1026; i++)
//         {
//             imagem_asfalto[i] = (int *)malloc(1026 * sizeof(int));
//         }
//
//         fscanf(arquivo_treino_asfalto,"%s", caminho_treino_asfalto);
//         FILE *file_asfalto = fopen(caminho_treino_asfalto, "r");
//
//         // Salva a imagem lida
//         for (int i = 0; i < 1025; i++)
//         {
//             for (int j = 0; j < 1025; j++)
//                 fscanf(file_asfalto, "%d%*c", &imagem_asfalto[i][j]);
//         }
//
//
//         // CONTINUAR COM O NECESSÁRIO PRA CADA IMAGEM DE TREINAMENTO DE ASFALTO
//
//
//         for(int i = 0; i < sizeof(imagem_asfalto); i++)
//         {
//             free(imagem_asfalto);
//         }
//         free(imagem_asfalto);
//         fclose(file_asfalto);
//     }
//
//     fclose(arquivo_treino_asfalto);
//
// //
// // Teste GRAMA
// //
//
//     FILE *arquivo_teste_grama = fopen("teste_grass.txt", "r");
//     char caminho_teste_grama[27];
//
//     for(int i = 0; i < 25; i++)
//     {
//         int **imagem_grama = (int **)malloc(1026 * sizeof(int *));
//         for(int i = 0; i < 1026; i++)
//         {
//             imagem_grama[i] = (int *)malloc(1026 * sizeof(int));
//         }
//
//         fscanf(arquivo_teste_grama,"%s", caminho_teste_grama);
//         FILE *file_grama = fopen(caminho_teste_grama, "r");
//
//         // Salva a imagem lida
//         for (int i = 0; i < 1025; i++)
//         {
//             for (int j = 0; j < 1025; j++)
//                 fscanf(file_grama, "%d%*c", &imagem_grama[i][j]);
//         }
//
//
//         // CONTINUAR AQUI COM O NECESSÁRIO PRA CADA IMAGEM DE TESTE DE GRAMA
//
//
//         for(int i = 0; i < sizeof(imagem_grama); i++)
//         {
//             free(imagem_grama);
//         }
//         free(imagem_grama);
//         fclose(file_grama);
//     }
//
//     fclose(arquivo_teste_grama);
//
// //
// // Teste ASFALTO
// //
//
//     FILE *arquivo_teste_asfalto = fopen("teste_asphalt.txt", "r");
//     char caminho_teste_asfalto[31];
//
//     for(int i = 0; i < 25; i++)
//     {
//         int **imagem_asfalto = (int **)malloc(1026 * sizeof(int *));
//         for(int i = 0; i < 1026; i++)
//         {
//             imagem_asfalto[i] = (int *)malloc(1026 * sizeof(int));
//         }
//
//         fscanf(arquivo_teste_asfalto,"%s", caminho_teste_asfalto);
//         FILE *file_asfalto = fopen(caminho_teste_asfalto, "r");
//
//         // Salva a imagem lida
//         for (int i = 0; i < 1025; i++)
//         {
//             for (int j = 0; j < 1025; j++)
//                 fscanf(file_asfalto, "%d%*c", &imagem_asfalto[i][j]);
//         }
//
//
//     // CONTINUAR AQUI COM O NECESSÁRIO PRA CADA IMAGEM DE TESTE DE ASFALTO
//
//
//         for(int i = 0; i < sizeof(imagem_asfalto); i++)
//         {
//             free(imagem_asfalto);
//         }
//         free(imagem_asfalto);
//         fclose(file_asfalto);
//     }
//
//     fclose(arquivo_teste_asfalto);
=======
#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("Teste Makefile\n");
>>>>>>> 8d7376fd6cccefb500ebdd11c41faf51d7cfb28d

    return 0;
}
