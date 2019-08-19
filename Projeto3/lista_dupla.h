#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char nome[101];
    char telefone[11];
    char endereco[11];
    int CEP;
    char niver[11];

    struct Node *next, *prev;
} Lista;

Lista *head, *tail;
unsigned long _size = 0;

Lista *crialista();
Lista *insere_contato(Lista *l, char nom[101], char tel[11], char ed[101], int cep, char ani[11]);
void imprime(Lista *l);
void remover_um(Lista *l, char nom[101]);
void visualizar(Lista *l, char nom[101]);
// Lista *grava_arquivo(Lista* l);

#endif
