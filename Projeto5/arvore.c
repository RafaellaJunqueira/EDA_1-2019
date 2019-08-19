// Rafaella Junqueira     16/0142628     Turma B


#include "arvore.h"
#define MAX_TAM (1<<20)
#define ALTURA_MAX 1000
int tam = -1;
int vetor[100];

Arv *Root = NULL;
int espaco = 3, imprime_prox;
int esquerda[ALTURA_MAX], direita[ALTURA_MAX];

Arv* loadTreeFromFile(const char *caminho)
{
    Arv *av = cria_arvore();
    int num;

    FILE *arquivo = fopen(caminho, "r");

    if(!arquivo)
    {
        printf("\nArquivo não encontrado!\n\n");
        exit(1);
    }

    tam = 0;
    while((fscanf(arquivo, "%d", &num)) != EOF)
    {
        vetor[tam] = num;
        av = insere_no(av, num);
        tam++;
    }

    fclose(arquivo);
    return av;
}
void showTree(Arv *raiz)
{
    system("clear");
    Root = raiz;
    if(!raiz)
    {
        printf("\nArvore não carregada!!\n\n");
    }
    if(tam == 0)
    {
        printf("Não há mais elementos!\n");
    }
    else
    {
        int i,j;
        int tree[44][120];
        for(i = 0; i < 44; i++)
        {
            for(j = 0; j < 120; j++)
            {
                tree[i][j]=0;
            }
        }

        if(-1 != le_arvore(raiz,16,0,60,tree))
        {
            for(i = 0; i < 35; i++)
            {
                for(j = 0; j < 100; j++)
                {
                    if(i == 0 || i == 17 || i == 26 || i == 31 || i == 34 || i == 36)
                    {
                        if(tree[i][j] == 0) printf(" ");
                        else printf("%d", tree[i][j]);
                    }
                    else
                    {
                        if((tree[i][j] == 0)) printf(" ");
                        else printf("%c",tree[i][j]);
                    }
                }
                printf("\n");
            }
        }
        else
        {
           Node *no_raiz;

           if(Root == NULL) return;

           no_raiz = cria_no(Root);
           preenche_galho(no_raiz);

           for (int i = 0; i < no_raiz->altura && i < ALTURA_MAX; i++)
               esquerda[i] = MAX_TAM;

           menor_esquerda(no_raiz, 0, 0);
           int xmin = 0;

           for (int i = 0; i < no_raiz->altura && i < ALTURA_MAX; i++)
               xmin = menor_node(xmin, esquerda[i]);
           for (int i = 0; i < no_raiz->altura; i++) {
               imprime_prox = 0;
               imprime_nivel(no_raiz, -xmin, i);
               printf("\n");
           }

           libera_no(no_raiz);
        }
    }
}
int isFullTree(Arv* root)
{

    if(root == NULL)
        return 1;

    if(root->esquerda == NULL && root->direita == NULL)
        return 1;

    if((root->esquerda) && (root->direita))
        return (isFullTree(root->esquerda) && isFullTree(root->direita));

    return 0;
}
Arv* searchValue(Arv* tree, int num)
{
    if(tree == NULL)
        return NULL;

    else if(tree->valor > num)
            return searchValue(tree->esquerda, num);
    else if(tree->valor < num)
            return searchValue(tree->direita, num);
    else
        return tree;
}
int getHeight(Arv* node)
{
    if(node==NULL)
        return 0;

    else
    {
        int laltura = getHeight(node->esquerda);
        int raltura = getHeight(node->direita);

        if(laltura > raltura)
        {
            return(laltura + 1);
        }
        else
            return(raltura + 1);
    }
}
Arv* removeValue(Arv* r, int valor)
{
    if(r == NULL) return NULL;

    for(int i = 0; i < tam; i++)
    {
        if(vetor[i] == valor)
        {
            for(i; i < tam; i++)
            {
                vetor[i] = vetor[i + 1];
            }
        }
    }
    tam--;

    libera_arvore(r);
    Arv *raiz = cria_arvore();
    for(int i = 0; i < tam; i++)
    {
        raiz = insere_no(raiz, vetor[i]);
    }

    return raiz;
}
void printInOrder(Arv* a)
{
    if(tam == 0)
    {
        printf("Não há mais elementos!\n");
    }
    else if(a != NULL && tam > 0)
    {
        printInOrder(a->esquerda);
        printf("%d ", a->valor);
        printInOrder(a->direita);
    }

}
void printPreOrder(Arv* a)
{
    if(tam == 0)
    {
        printf("Não há mais elementos!\n");
    }

    else if(a != NULL && tam > 0)
    {
        printf("%d ", a->valor);
        printPreOrder(a->esquerda);
        printPreOrder(a->direita);
    }
}
void printPostOrder (Arv* a)
{
    if(tam == 0)
    {
        printf("Não há mais elementos!\n");
    }
    else if(a != NULL && tam > 0)
    {
        printPostOrder(a->esquerda);
        printPostOrder(a->direita);
        printf("%d ", a->valor);
    }
}
void balanceTree(Arv *raiz)
{
    if(balanceada(raiz) == false){}
}
Arv* cria_arvore()
{
    return NULL;
}
void libera_arvore(Arv *no)
{
    if(no == NULL) return;
    libera_arvore(no->esquerda);
    libera_arvore(no->direita);
    free(no);
}
Arv* insere_no(Arv* a, int v)
{
    if(a == NULL)
    {
        a = (Arv*)malloc(sizeof(Arv));
        a->valor = v;
        a->esquerda = a->direita = NULL;
    }
    else if(v < a->valor)
        a->esquerda = insere_no(a->esquerda, v);
    else
        a->direita = insere_no(a->direita, v);

    return a;
}
int pega_nivel(Arv *node, int valor, int nivel)
{
    if(node == NULL)
        return 0;

    if(node->valor == valor)
        return nivel;

    int nivel_abaixo = pega_nivel(node->esquerda, valor, nivel + 1);
    if(nivel_abaixo != 0)
        return nivel_abaixo;

    nivel_abaixo = pega_nivel(node->direita, valor, nivel + 1);
    return nivel_abaixo;
}
int pega_pai(Arv *raiz, int valor, int altura)
{
    if((raiz->esquerda != NULL) && valor < raiz->valor)
    {
        if(raiz->esquerda->valor == valor)
            return raiz->valor;

        pega_pai(raiz->esquerda, valor, altura);
    }
    else if((raiz->direita != NULL))
    {
        if(raiz->direita->valor == valor)
            return raiz->valor;

        pega_pai(raiz->direita, valor, altura);
    }
}
int pega_irmao(Arv *raiz, int valor, int altura)
{
    if((raiz->esquerda != NULL) && valor < raiz->valor)
    {
        if(raiz->esquerda->valor == valor)
        {
            if(raiz->direita != NULL)
                return raiz->direita->valor;
            else
                return 0;
        }
        pega_irmao(raiz->esquerda, valor, altura);
    }

    else if((raiz->direita != NULL))
    {
        if(raiz->direita->valor == valor)
        {
            if(raiz->esquerda != NULL)
                return raiz->esquerda->valor;
            else
                return 0;
        }
        pega_irmao(raiz->direita, valor, altura);
    }
}
bool balanceada(Arv *tree)
{
   int lh;
   int rh;

   if(tree == NULL)
        return true;

   lh = getHeight(tree->esquerda);
   rh = getHeight(tree->direita);

   if(abs(lh-rh) <= 1 && balanceada(tree->esquerda) && balanceada(tree->direita))
        return true;

   return false;
}
int le_arvore(Arv *no_atual,int max,int row,int col,int av[44][120])
{
    int i = 0, m = 0, n = 0;
    int r = row;

    if(no_atual == NULL)
        return -1;

    if(max == 1 && (no_atual->esquerda != NULL || no_atual->direita != NULL))
        return -1;

    av[row][col] = no_atual->valor;

    if(no_atual->esquerda != NULL)
    {
        while(i++ < max)
        {
            av[++r][col - i] = '/';
        }
        m = le_arvore(no_atual->esquerda, max / 2, r + 1, col- max - 1, av);
    }

    i = 0;
    r = row;
    if(no_atual->direita != NULL)
    {
        while(i++<max)
        {
            av[++r][col + i] = '\\';
        }
        n = le_arvore(no_atual->direita, max / 2, r + 1, col + max + 1, av);
    }
    if(m == -1 || n == -1) return -1;
    else return 0;
}
int menor_node(int x, int y)
{
    if(x < y)  return x;
    else return y;
}
int maior_node(int x, int y)
{
    if(x > y) return x;
    else return y;
}
Node *cria_no(Arv *n)
{
    Node *no;
    if(n == NULL) return NULL;

    no = malloc(sizeof(Node));
    no->esquerda = cria_no(n->esquerda);
    no->direita = cria_no(n->direita);
    no->tipo = 0;

    if(no->esquerda != NULL)
    {
        no->esquerda->tipo = -1;
    }
    if(no->direita != NULL)
    {
        no->direita->tipo = 1;
    }

    sprintf(no->descricao, "%d", n->valor);
    no->valor = strlen(no->descricao);

    return no;
}
void libera_no(Node *no)
{
    if(no == NULL) return;
    libera_no(no->esquerda);
    libera_no(no->direita);
    free(no);
}
void preenche_galho(Node *no)
{
    int alturaMin, delta;
    if(no == NULL) return;

    preenche_galho(no->esquerda);
    preenche_galho(no->direita);

    if(no->direita == NULL && no->esquerda == NULL)
    {
        no->galho = 0;
    }
    else
    {
        if(no->esquerda != NULL)
        {
            for (int i = 0; i < no->esquerda->altura && i < ALTURA_MAX; i++)
            {
                direita[i] = -MAX_TAM;
            }
            maior_direita(no->esquerda, 0, 0);
            alturaMin = no->esquerda->altura;
        }
        else
        {
            alturaMin = 0;
        }
        if(no->direita != NULL)
        {
            for(int i = 0; i < no->direita->altura && i < ALTURA_MAX; i++)
            {
                esquerda[i] = MAX_TAM;
            }

            menor_esquerda(no->direita, 0, 0);
            alturaMin = menor_node(no->direita->altura, alturaMin);
        }
        else
        {
            alturaMin = 0;
        }

        delta = 4;
        for(int i = 0; i < alturaMin; i++)
        {
            delta = maior_node(delta, espaco + 1 + direita[i] - esquerda[i]);
        }
        if(((no->esquerda != NULL && no->esquerda->altura == 1) || (no->direita != NULL && no->direita->altura == 1)) && delta > 4)
        {
            delta--;
        }

        no->galho = ((delta + 1) / 2) - 1;
    }

    int altura = 1;
    if(no->esquerda != NULL)
    {
        altura = maior_node(no->esquerda->altura + no->galho + 1, altura);
    }
    if(no->direita != NULL)
    {
        altura = maior_node(no->direita->altura + no->galho + 1, altura);
    }
    no->altura = altura;
}
void imprime_nivel(Node *no, int x, int nivel)
{
    if(no == NULL) return;
    int esquerdinha = (no->tipo == -1);
    if(nivel == 0)
    {
        int i;
        for (i = 0; i < (x - imprime_prox - ((no->valor - esquerdinha) / 2)); i++)
            printf(" ");

        imprime_prox += i;
        printf("%s", no->descricao);
        imprime_prox += no->valor;
    }
    else if(no->galho >= nivel)
    {
        if(no->esquerda != NULL)
        {
            int i;
            for(i = 0; i < (x - imprime_prox - (nivel)); i++)
            {
                printf(" ");
            }

            imprime_prox += i;
            printf("/");
            imprime_prox++;
        }
        if(no->direita != NULL)
        {
            int i;
            for (i = 0; i < (x - imprime_prox + (nivel)); i++)
                printf(" ");

            imprime_prox += i;
            printf("\\");
            imprime_prox++;
        }
    }
    else
    {
        imprime_nivel(no->esquerda, x - no->galho - 1, nivel - no->galho - 1);
        imprime_nivel(no->direita, x + no->galho + 1, nivel - no->galho - 1);
    }
}
void menor_esquerda(Node *no, int x, int y)
{
    if(no == NULL) return;

    int esquerdinha = (no->tipo == -1);
    esquerda[y] = menor_node(esquerda[y], x - ((no->valor - esquerdinha) / 2));

    if(no->esquerda != NULL)
    {
        for(int i = 1; i <= no->galho  && y + i < ALTURA_MAX; i++)
        {
            esquerda[y + i] = menor_node(esquerda[y + i], x - i);
        }
    }

    menor_esquerda(no->esquerda, x - no->galho - 1, y + no->galho + 1);
    menor_esquerda(no->direita, x + no->galho + 1, y + no->galho + 1);
}
void maior_direita(Node *no, int x, int y)
{
    if(no == NULL) return;

    int ttesquerda = (no->tipo != -1);
    direita[y] = maior_node(direita[y], x + ((no->valor - ttesquerda) / 2));

    if(no->direita != NULL)
    {
        for(int i = 1; i <= no->galho && y + i < ALTURA_MAX; i++)
        {
            direita[y + i] = maior_node(direita[y + i], x + i);
        }
    }
    maior_direita(no->esquerda, x - no->galho - 1, y + no->galho + 1);
    maior_direita(no->direita, x + no->galho + 1, y + no->galho + 1);
}


int main()
{
    Arv *raiz = cria_arvore();


    int escolha = 0;
    while(escolha != 11)
    {
        if(tam == 0)
        {
            libera_arvore(raiz);
        }
    menu:  printf("-----------------------------\n");
           printf("         MENU - ÁRVORE       \n");
           printf("-----------------------------\n");
           printf(" 1- Carregar árvore          \n");
           printf(" 2- Imprimir árvore          \n");
           printf(" 3- Árvore está cheia?       \n");
           printf(" 4- Buscar valor             \n");
           printf(" 5- Altura da árvore         \n");
           printf(" 6- Remover valor            \n");
           printf(" 7- Imprimir 'InOrder'       \n");
           printf(" 8- Imprimir 'PreOrder'      \n");
           printf(" 9- Imprimir 'PostOrder'     \n");
           printf(" 10- Árvore está balanceada? \n");
           printf(" 11- Sair                    \n");
           printf("-----------------------------  \n");
           printf("\nOpcao: ");

           scanf("%d", &escolha);

       switch(escolha)
       {
                case 1:
                {
                    char ok;    
                    char nome[100];
                    char caminho[5] = "BSTs/";

                    printf("Digite o nome do arquivo (sem a extensão): ");
                    scanf("%s", nome);
                    strcat(caminho, nome);
                    strcat(caminho, ".txt");
                    raiz = loadTreeFromFile(caminho);
                    system("clear");
                    printf("\n\nÁrvore carregada!\n\n");
                    strcpy(caminho, "BSTs/");

                    break;
                }
                case 2:
                {
                    showTree(raiz);

                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }

                    break;
                }
                case 3:
                {
                    if(isFullTree(raiz) == 1) printf("\nÁrvore cheia!\n");
                    else printf("\nÁrvore NÃO cheia\n");
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                    break;
                }
                case 4:
                {
                    if(!raiz) printf("\nÁrvore vazia ou não carregada!\n");

                    else
                    {
                        int procura;
                        printf("\nDigite o valor procurado: ");
                        scanf("%d", &procura);

                        if(searchValue(raiz, procura))
                        {
                            if(procura == raiz->valor)
                            {
                                printf("\nNível : %d (raiz da árvore)\n", pega_nivel(raiz, procura, 1));
                            }
                            else
                            {
                                int irmao = pega_irmao(raiz, procura, pega_nivel(raiz, procura, 1) - 1);
                                printf("\nNivel : %d\n", pega_nivel(raiz, procura, 1));
                                printf("Pai   : %d\n", pega_pai(raiz, procura, pega_nivel(raiz, procura, 1) - 1));
                                if(irmao)
                                printf("Irmao : %d\n", irmao);
                                else
                                printf("Irmao : Não possui!\n");
                            }
                        }
                        else
                        printf("\n\nValor não encontrado na árvore!\n\n");
                    }
                        char x;
                        while(scanf("%c", &x))
                        {
                            if(x == 'x' || x == 'X')
                            {
                                system("clear");
                                goto menu;
                            }
                            else
                                printf("\nDigite 'x' para voltar ao menu! ");
                        }
                }
                case 5:
                {
                    if(!raiz)
                        printf("\n\nArvore vazia ou não carregada!\n\n");
                    else
                        printf("\nAltura = %d\n", getHeight(raiz));
                        char x;
                        while(scanf("%c", &x))
                        {
                            if(x == 'x' || x == 'X')
                            {
                                system("clear");
                                goto menu;
                            }
                            else
                                printf("\nDigite 'x' para voltar ao menu! ");
                        }
                    break;
                }
                case 6:
                {
                    if(!raiz)
                        printf("\n\nÁrvore vazia ou não carregada!\n\n");
                    else
                    {
                        int valor;
                        printf("\nDigite o valor a ser removido: ");
                        scanf("%d", &valor);

                        if(searchValue(raiz, valor))
                        {
                            removeValue(raiz, valor);
                            printf("\n\nNó removido!\n\n");
                        }
                        else
                            printf("\n\nValor não encontrado!\n\n");
                    }
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                    break;
                }
                case 7:
                {
                    if(!raiz)
                        printf("\n\nÁrvore vazia ou não carregada!\n\n");
                    else
                    {
                        printf("\n\n");
                        printInOrder(raiz);
                        printf("\n\n");
                    }
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                }
                case 8:
                {
                    if(!raiz)
                        printf("\n\nÁrvore vazia ou não carregada!\n\n");
                    else
                    {
                        printf("\n\n");
                        printPreOrder(raiz);
                        printf("\n\n");
                    }
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                    break;
                }
                case 9:
                {
                    if(!raiz)
                        printf("\n\nÁrvore vazia ou não carregada!\n\n");
                    else
                    {
                        printf("\n\n");
                        printPostOrder(raiz);
                        printf("\n\n");
                    }
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                    break;
                }
                case 10:
                {
                    if(!raiz)
                        printf("\n\nArvore vazia ou não carregada!\n\n");
                    else
                        if(balanceada(raiz))
                            printf("\n\nÁrvore Balanceada!\n\n");
                        else
                            printf("\n\nÁrvore NÃO balaceada!\n\n");
                    char x;
                    while(scanf("%c", &x))
                    {
                        if(x == 'x' || x == 'X')
                        {
                            system("clear");
                            goto menu;
                        }
                        else
                            printf("\nDigite 'x' para voltar ao menu! ");
                    }
                    break;
                }
                default:
                    break;
         }
    }

    return 0;
}
