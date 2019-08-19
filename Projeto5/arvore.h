// Rafaella Junqueira     16/0142628     Turma B


#ifndef ARVORE_H
#define ARVORE_H

#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Arvore{
    int valor;
    struct Arvore* esquerda;
    struct Arvore* direita;
}Arv;

typedef struct Node{
    struct Node *esquerda, *direita;
    int valor, galho, altura, tipo;
    char descricao[11];
}Node;

Arv* loadTreeFromFile(const char *caminho);
void showTree(Arv *raiz);
int isFullTree(Arv* raiz);
Arv* searchValue(Arv* tree, int num);
int getHeight(Arv *tree);
Arv* removeValue(Arv* raiz, int valor);
void printInOrder(Arv* a);
void printPreOrder(Arv* a);
void printPostOrder(Arv* a);
void balanceTree(Arv *raiz);
Arv* cria_arvore(void);
void libera_arvore(Arv *no);
Arv* insere_no(Arv* a, int valor);
int pega_nivel(Arv *node, int valor, int nivel);
int pega_pai(Arv *raiz, int valor, int altura);
int pega_irmao(Arv *raiz, int valor, int altura);
bool balanceada(Arv *tree);
int le_arvore(Arv *no_atual,int max,int row,int col,int av[44][120]);
int menor_node(int x, int y);
int maior_node(int x, int y);
Node *cria_no(Arv *n);
void libera_no(Node *no);
void preenche_galho(Node *no);
void imprime_nivel(Node *no, int x, int nivel);
void menor_esquerda(Node *no, int x, int y);
void maior_direita(Node *no, int x, int y);

#endif
