#include "ilbp.h"
#include "glcm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// sorteia aleatoriamente 50 números, 25 pra teste e 25 pra treinamento
int *sorteio_teste_treino()
{
    srand(time(NULL));
    int *n = (int *)malloc(50 * sizeof(int));

    int x = 1, y = 0;
    n[0] = rand() % 50 + 1;

    while (x < 50)
    {
        n[x] = rand() % 50 + 1;
        y = 0;

        while (y < x)
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

// Gera arquivos com os caminhos para as imagens sorteadas (grama teste, grama treino, asfalto teste e asfalto treinamento).
// Têm que estar em DataSet/grass e DataSet/asphalt
int salva_arquivos(int *vetor, int teste_treino, int grama_asfalto)
{
    char nome[20];
    char diretorio[256];
    int i = 0;
    int tipo;

    if (teste_treino == 0 && grama_asfalto == 0)
    {
        strcpy(nome, "teste_grass.txt");
        strcpy(diretorio, "DataSet/grass/grass_");
        tipo = 0;
    }
    else if (teste_treino == 0 && grama_asfalto == 1)
    {
        strcpy(nome, "teste_asphalt.txt");
        strcpy(diretorio, "DataSet/asphalt/asphalt_");
        tipo = 1;
    }
    else if (teste_treino == 1 && grama_asfalto == 0)
    {
        strcpy(nome, "treino_grass.txt");
        strcpy(diretorio, "DataSet/grass/grass_");
        tipo = 2;
    }
    else if (teste_treino == 1 && grama_asfalto == 1)
    {
        strcpy(nome, "treino_asphalt.txt");
        strcpy(diretorio, "DataSet/asphalt/asphalt_");
        tipo = 3;
    }
    else
    {
        printf("ERRO");
    }
    // printf("Criando: %s \n", nome);
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
// Fazer operações ILBP
void ILBP(double *number_ilbp, int *image)
{
    for (int i = 1; i < 1024; i++)
    {
        for (int j = 1; j < 1024; j++)
        {
            // Pega area envolta dos pixels
            int *area = (int *)malloc(3 * 3 * sizeof(int));
            double sum = get_area_pixel(i, j, image, area);

            // Seta a matriz binaria
            int *binario = (int *)malloc(3 * 3 * sizeof(int));
            set_binary_matrix(area, binario, sum);

            // Caracol
            char *bin_str = (char *)malloc(9 * sizeof(char));
            transform_bin_caracol(bin_str, binario);

            // Pega o resultado do ilbp
            int result_ilbp = get_ilbp_numb(bin_str);

            // Seta vetor ilbp resultados
            set_ilbp_number_vector(number_ilbp, result_ilbp);

            // limpa memoria
            free(area);
            free(bin_str);
            free(binario);
        }
    }
}

int main()
{
    int *ordem_imagem_asfalto;
    int *ordem_imagem_grama;

    ordem_imagem_asfalto = sorteio_teste_treino();
    ordem_imagem_grama = sorteio_teste_treino();

    double *media_grass, *media_asphalt;

    int asfalto_treino[25] = {0};
    int asfalto_teste[25] = {0};
    int grama_treino[25] = {0};
    int grama_teste[25] = {0};

    // printf("Sorteio de arquivos de Treinamento!\n");
    for (int i = 0; i < 25; ++i)
    {
        asfalto_treino[i] = *(ordem_imagem_asfalto + i);
        grama_treino[i] = *(ordem_imagem_grama + i);
    }

    // printf("Sorteio de arquivos de Teste!\n");
    for (int i = 0; i < 50; ++i)
    {
        asfalto_teste[i - 25] = *(ordem_imagem_asfalto + i);
        grama_teste[i - 25] = *(ordem_imagem_grama + i);
    }

    int arquivos_teste_grama = salva_arquivos(grama_teste, 0, 0);
    int arquivos_teste_asfalto = salva_arquivos(asfalto_teste, 0, 1);
    int arquivos_treino_grama = salva_arquivos(grama_treino, 1, 0);
    int arquivos_treino_asfalto = salva_arquivos(asfalto_treino, 1, 1);

    // Pega cada caminho salvo nos arquivos
    FILE *p_asphalt = fopen("treino_asphalt.txt", "r");
    FILE *p_grass = fopen("treino_grass.txt", "r");

    FILE *q_asphalt = fopen("teste_asphalt.txt", "r");
    FILE *q_grass = fopen("teste_grass.txt", "r");

    char path_asphalt[31];
    char path_grass[27];
    char caminho_asphalt[31];
    char caminho_grass[27];

    printf("TREINANDO GRAMA\n");
    media_grass = (double *)calloc(1024, sizeof(double));
    //
    //
    // TREINAMENTO GRAMA
    //
    //

    // Abre cada imagem de grama
    for (int i = 0; i < 25; i++)
    {
        // Aloca espaços para armazenar imagens
        int **grass_image = (int **)malloc(1026 * sizeof(int *));

        for (int i = 0; i < 1026; i++)
            grass_image[i] = (int *)malloc(1026 * sizeof(int));

        // fgets(path_grass, 27, p_grass);
        fscanf(p_grass,"%s",path_grass);
        printf("%s\n",path_grass);
        FILE *f_grass = fopen(path_grass, "r");

        // Salva a imagem lida
        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                fscanf(f_grass, "%d%*c", &grass_image[i][j]);
        }
        // Aloca espaço para os vetores de resultados
        double *freq_glcm = (double *)malloc(24 * sizeof(double));
        double *freq_ilbp = (double *)malloc(512 * sizeof(double));

        // Adequa matriz para ser lida pelo ilbp
        int *img_grass = (int *)malloc(1026 * 1026 * sizeof(int));

        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                *(img_grass + (i * 1025) + j) = grass_image[i][j];
        }

        // Chama ilbp para imagens de treino
        ILBP(freq_ilbp, img_grass);

        // Chama glcm para imagens de treino
        glcm(grass_image, freq_glcm);

        // Concatena vetores
        int *vetor_grass = (int *)malloc(536*sizeof(int));

        for (int i = 0; i < 512; i++)
        {
            *(vetor_grass + i) = freq_ilbp[i];
        }
        for(int i = 0; i < 24; i++){
            *(vetor_grass + 511 + i) = freq_glcm[i];
        }

        // Dados para normalizar vetor
        int menor_grass = 9999999;
        int maior_grass = -1;

        // Acha o menor e o maior número
        for (int i = 0; i < 536; i++)
        {
            if (*(vetor_grass + i) < menor_grass)
                menor_grass = *(vetor_grass + i);
            if (*(vetor_grass + i) > maior_grass)
                maior_grass = *(vetor_grass + i);
        }

        // Normalizando vetor e construindo vetor media
        for (int i = 0; i < 536; i++)
        {
            if(*(vetor_grass+i) != 0)
                *(media_grass + i) += (((*(vetor_grass + i)) - menor_grass) / (maior_grass - menor_grass))/25;
        }

        for (int i = 0; i < 1026; i++)
        {
            free(grass_image[i]);
        }
        free(grass_image);
        fclose(f_grass);
        free(img_grass);
        free(vetor_grass);
        free(freq_ilbp);
        free(freq_glcm);
    }
    printf("TREINOU GRAMA\n");

    printf("TREINANDO ASFALTO\n");
    media_asphalt = (double *)calloc(1024, sizeof(double));
    //
    //
    // TREINAMENTO ASFALTO
    //
    //

    // Abre cada imagem de grama
    for (int i = 0; i < 25; i++)
    {
        // Aloca espaços para armazenar imagens
        int **asphalt_image = (int **)malloc(1026 * sizeof(int *));

        for (int i = 0; i < 1026; i++)
            asphalt_image[i] = (int *)malloc(1026 * sizeof(int));

        // fgets(path_asphalt, 27, p_asphalt);
        fscanf(p_asphalt,"%s",path_asphalt);
        printf("%s\n",path_asphalt);
        FILE *f_asphalt = fopen(path_asphalt, "r");

        // Salva a imagem lida
        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                fscanf(f_asphalt, "%d%*c", &asphalt_image[i][j]);
        }

        // Aloca espaço para os vetores de resultados
        double *freq_glcm = (double *)malloc(24 * sizeof(double));
        double *freq_ILBP = (double *)malloc(512 * sizeof(double));

        // Adequa matriz para ser lida pelo ILBP
        int *img_asphalt = (int *)malloc(1026 * 1026 * sizeof(int));

        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                *(img_asphalt + (i * 1025) + j) = asphalt_image[i][j];
        }

        // Chama ILBP para imagens de treino
        ILBP(freq_ILBP, img_asphalt);

        // Chama glcm para imagens de treino
        glcm(asphalt_image, freq_glcm);

        // Concatena vetores
        int *vetor_asphalt = (int *)malloc(536*sizeof(int));

        for (int i = 0; i < 512; i++)
        {
            *(vetor_asphalt + i) = freq_ILBP[i];
        }
            
        for(int i = 0; i < 24; i++){
            *(vetor_asphalt + 511 + i) = freq_glcm[i];
        }

        // Dados para normalizar vetor
        int menor_asphalt = 9999999;
        int maior_asphalt = -1;

        // Acha o menor e o maior número
        for (int i = 0; i < 1024; i++)
        {
            if (*(vetor_asphalt + i) < menor_asphalt)
                menor_asphalt = *(vetor_asphalt + i);
            if (*(vetor_asphalt + i) > maior_asphalt)
                maior_asphalt = *(vetor_asphalt + i);
        }

        // Normalizando vetor e construindo vetor media
        for (int i = 0; i < 536; i++)
        {
            *(media_asphalt + i) += (((*(vetor_asphalt + i)) - menor_asphalt) / (maior_asphalt - menor_asphalt))/25;
        }

        for (int i = 0; i < 1026; i++)
            free(asphalt_image[i]);
        free(asphalt_image);
        fclose(f_asphalt);
        free(img_asphalt);
        free(vetor_asphalt);
        free(freq_ILBP);
        free(freq_glcm);
    }
    printf("TREINOU ASFALTO\n");
    printf("TESTES\n");
    //
    //
    // TESTE GRAMA
    //
    //
    double acertos = 0, falsa_rejeicao = 0, falsa_aceitacao = 0;

    for (int i = 0; i < 25; i++)
    {
        // Aloca espaços para armazenar imagens
        int **grass_image_teste = (int **)malloc(1026 * sizeof(int *));

        for (int i = 0; i < 1026; i++)
            grass_image_teste[i] = (int *)malloc(1026 * sizeof(int));

        // fgets(caminho_grass, 27, q_grass);
        fscanf(q_grass,"%s",caminho_grass);
        printf("%s\n",caminho_grass);
        FILE *f_grass = fopen(caminho_grass, "r");

        // Salva a imagem lida
        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                fscanf(f_grass, "%d%*c", &grass_image_teste[i][j]);
        }

        // Aloca espaço para os vetores de resultados
        double *freq_glcm_teste = (double *)malloc(24 * sizeof(double));
        double *freq_ilbp_teste = (double *)malloc(512 * sizeof(double));

        // Adequa matriz para ser lida pelo ILBP
        int *img_grass_teste = (int *)malloc(1026 * 1026 * sizeof(int));

        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                *(img_grass_teste + (i * 1025) + j) = grass_image_teste[i][j];
        }

        // Chama ILBP para imagens de teste
        ILBP(freq_ilbp_teste, img_grass_teste);

        // Chama glcm para imagens de treino
        glcm(grass_image_teste, freq_glcm_teste);

        // Concatena vetores
        int *vetor_grass_teste = (int *)malloc(536*sizeof(int));

        for (int i = 0; i < 512; i++)
        {
            *(vetor_grass_teste + i) = freq_ilbp_teste[i];
        }
        for(int i = 0; i < 24;i++){
            *(vetor_grass_teste + 511 + i) = freq_glcm_teste[i];
        }

        // Dados para normalizar vetor
        int menor_grass_teste = 9999999;
        int maior_grass_teste = -1;

        // Acha o menor e o maior número
        for (int i = 0; i < 536; i++)
        {
            if (*(vetor_grass_teste + i) < menor_grass_teste)
                menor_grass_teste = *(vetor_grass_teste + i);
            if (*(vetor_grass_teste + i) > maior_grass_teste)
                maior_grass_teste = *(vetor_grass_teste + i);
        }

        double *normal_grass_teste = (double *)calloc(536, sizeof(double));

        // Normalizando vetor
        for (int i = 0; i < 536; i++)
        {
            *(normal_grass_teste + i) = (((*(vetor_grass_teste + i)) - menor_grass_teste) / (maior_grass_teste - menor_grass_teste));
        }

        double dist_grass;
        dist_grass = distancia_euclidiana(normal_grass_teste, media_grass);

        double dist_asphalt;
        dist_asphalt = distancia_euclidiana(normal_grass_teste, media_asphalt);

        if (dist_grass < dist_asphalt)
            acertos++;
        else
            falsa_rejeicao++;

        for (int i = 0; i < 1026; i++)
            free(grass_image_teste[i]);
        free(grass_image_teste);
        free(normal_grass_teste);
        free(vetor_grass_teste);
        free(img_grass_teste);
        free(freq_ilbp_teste);
        free(freq_glcm_teste);
        fclose(f_grass);
    }

    //
    //
    // TESTE ASFALTO
    //
    //

    for (int i = 0; i < 25; i++)
    {
        // Aloca espaços para armazenar imagens
        int **asphalt_image_teste = (int **)malloc(1026 * sizeof(int *));

        for (int i = 0; i < 1026; i++)
            asphalt_image_teste[i] = (int *)malloc(1026 * sizeof(int));

        // fgets(caminho_asphalt, 27, q_asphalt);
        fscanf(q_grass,"%s",caminho_asphalt);
        printf("%s\n",caminho_asphalt);
        FILE *f_asphalt = fopen(caminho_grass, "r");

        // Salva a imagem lida
        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                fscanf(f_asphalt, "%d%*c", &asphalt_image_teste[i][j]);
        }

        // Aloca espaço para os vetores de resultados
        double *freq_glcm_teste = (double *)malloc(24 * sizeof(double));
        double *freq_ilbp_teste = (double *)malloc(512 * sizeof(double));

        // Adequa matriz para ser lida pelo ilbp
        int *img_asphalt_teste = (int *)malloc(1026 * 1026 * sizeof(int));

        for (int i = 0; i < 1025; i++)
        {
            for (int j = 0; j < 1025; j++)
                *(img_asphalt_teste + (i * 1025) + j) = asphalt_image_teste[i][j];
        }

        // Chama ilbp para imagens de teste
        ILBP(freq_ilbp_teste, img_asphalt_teste);

        // Chama glcm para imagens de treino
        glcm(asphalt_image_teste, freq_glcm_teste);

        // Concatena vetores
        int *vetor_asphalt_teste = (int *)malloc(536*sizeof(int));

        for (int i = 0; i < 512; i++)
        {
            *(vetor_asphalt_teste + i) = freq_ilbp_teste[i];
        }
        for(int i = 0; i < 24; i++){    
            *(vetor_asphalt_teste + 511 + i) = freq_glcm_teste[i];
        }

        // Dados para normalizar vetor
        int menor_asphalt_teste = 9999999;
        int maior_asphalt_teste = -1;

        // Acha o menor e o maior número
        for (int i = 0; i < 536; i++)
        {
            if (*(vetor_asphalt_teste + i) < menor_asphalt_teste)
                menor_asphalt_teste = *(vetor_asphalt_teste + i);
            if (*(vetor_asphalt_teste + i) > maior_asphalt_teste)
                maior_asphalt_teste = *(vetor_asphalt_teste + i);
        }

        double *normal_asphalt_teste = (double *)calloc(536, sizeof(double));

        // Normalizando vetor
        for (int i = 0; i < 536; i++)
        {
            *(normal_asphalt_teste + i) = (((*(vetor_asphalt_teste + i)) - menor_asphalt_teste) / (maior_asphalt_teste - menor_asphalt_teste));
        }

        double dist_grass;
        dist_grass = distancia_euclidiana(normal_asphalt_teste, media_grass);

        double dist_asphalt;
        dist_asphalt = distancia_euclidiana(normal_asphalt_teste, media_asphalt);

        if (dist_grass > dist_asphalt)
            acertos++;
        else
            falsa_rejeicao++;

        for (int i = 0; i < 1026; i++)
            free(asphalt_image_teste[i]);
        free(asphalt_image_teste);

        free(normal_asphalt_teste);
        free(vetor_asphalt_teste);
        free(img_asphalt_teste);
        free(freq_ilbp_teste);
        free(freq_glcm_teste);
        fclose(f_asphalt);
    }

    printf("Acertos: %lf\n",acertos);
    printf("Falsa Rejeicao: %lf\n",falsa_rejeicao);
    printf("Falsa Aceitacao: %lf\n",falsa_aceitacao);

    free(media_grass);
    free(media_asphalt);
    free(ordem_imagem_grama);
    free(ordem_imagem_asfalto);
    fclose(p_asphalt);
    fclose(p_grass);
    fclose(q_asphalt);
    fclose(q_grass);

    return 0;
}
