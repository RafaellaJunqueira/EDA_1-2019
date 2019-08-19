#include <stdlib.h>
#include <stdio.h>


typedef struct Lista{
        char n[100];
        struct Lista *prox;
}tlista;

tlista *lu_insereinicio(tlista *plst, char pn[100])
{
       tlista *aux;
       aux = (tlista*)malloc(sizeof(tlista));
       aux -> n[100] = pn[100];
       aux -> prox = plst;
       return aux;
}

void lu_exibelista(tlista *plst)
{
     tlista *aux = plst;

     while (aux != NULL)
     {
           printf("%s, ", aux -> n);
           aux = aux -> prox;
     }
}

int main()
{
    char num[100];
    tlista *list;
    list = NULL;
    FILE *arquivo;

    arquivo = fopen("contatos.txt","r");

    if (arquivo)
       {
           do
             {
                fscanf(arquivo,"%s",num );
                list = lu_insereinicio(list, num);
             }while(!feof(arquivo));
         }

    lu_exibelista(list); // EXIBE A LISTA
    fclose(arquivo); // FECHA O ARQUIVO
    system("pause");
}
