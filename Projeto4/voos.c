// Rafaella Junqueira  -  16/0142628
// Turma B

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct no No;
struct no
{
    char* nome;
    char* tipo;
    int combustivel;
    No* next;
};
typedef struct head
{
    No* inicio;
    No* fim;
} Head;
int sorteia(int lower, int upper, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
    }
}
int main()
{
    srand(time(NULL));

	int num_voos;
	int num_aprox = sorteia(10, 32, 1);
    int num_decol = sorteia(10, 32, 1);

    num_voos = num_aprox + num_decol;

    int vetor_voos[num_voos], vetor_decol[num_decol], vetor_aprox[num_aprox];

	int pista = 0;
    int sos = 0;
    int hora_atual = 0, minuto_atual = 0;
    int cont = 0;

    vetor_voos[0] = rand() % 63 + 1;

    int i = 1, j = 0;
    while(i < num_voos)
    {
        vetor_voos[i] = rand() % 63 + 1;
        j = 0;

        while(j < i){
            if(vetor_voos[j] == vetor_voos[i])
            {
                --i;
                break;
            }
            ++j;
        }
        ++i;
    }

    int k = 0;
    for(i = 0; i < num_aprox; i++)
    {
        vetor_aprox[i] = vetor_voos[i];
        k++;
    }

    for(i = 0; i < num_decol; i++)
    {
        vetor_decol[i] = vetor_voos[k];
        k++;
    }

    char cod_avioes[64][7] = {  "VG3001", "JJ4404", "LN7001", "TG1501",
                                "GL7602", "TT1010", "AZ1009", "AZ1008",
                                "AZ1010", "TG1506", "VG3002", "JJ4402",
                                "GL7603", "RL7880", "AL0012", "TT4544",
                                "TG1505", "VG3003", "JJ4403", "JJ4401",
                                "LN7002", "AZ1002", "AZ1007", "GL7604",
                                "AZ1006", "TG1503", "AZ1003", "JJ4403",
                                "AZ1001", "LN7003", "AZ1004", "TG1504",
                                "AZ1005", "TG1502", "GL7601", "TT4500",
                                "RL7801", "JJ4410", "GL7607", "AL0029",
                                "VV3390", "VV3392", "GF4681", "GF4690",
                                "AZ1020", "JJ4435", "VG3010", "LF0920",
                                "AZ1065", "LF0978", "RL7867", "TT4502",
                                "GL7645", "LF0932", "JJ4434", "TG1510",
                                "TT1020", "AZ1098", "BA2312", "VG3030",
                                "BA2304", "KL5609", "KL5610", "KL5611"
                            };

    No* lista = NULL;
    Head* head = (Head*)malloc(sizeof(Head));
    head->inicio = NULL;
    head->fim = NULL;

    for(i = 0; i < num_aprox; i++)
    {
        No* atual = lista;
        No* anterior = NULL;
        int comb_sorteado = sorteia(0,12,1);

        No* novo = (No*)malloc(sizeof(No));
        novo->nome = cod_avioes[vetor_aprox[i]];
        novo->tipo = "P";
        novo->combustivel = comb_sorteado;

        if(atual == NULL)
        {
            novo->next = NULL;
            lista = novo;
        }
        else
        {
            while(atual != NULL && atual->combustivel < comb_sorteado)
            {
                anterior = atual;
                atual = atual->next;
            }
            novo->next = atual;

            if (anterior == NULL)
            {
                lista = novo;
            }
            else
            {
                anterior->next = novo;
            }
        }
    }

    for(i = 0; i < num_decol; i++)
    {
        No* aux = head->inicio;
        int comb_sorteado = -1;

        No* novo = (No*)malloc(sizeof(No));
        novo->nome = cod_avioes[vetor_decol[i]];
        novo->tipo = "D";
        novo->combustivel = comb_sorteado;
        novo->next = NULL;

        if(head->fim == NULL)
        {
            head->inicio = novo;
            head->fim = novo;
        }
        else
        {
            head->fim->next = novo;
            head->fim = novo;
        }
    }

    No* aux2 = lista;
    while(aux2->next != NULL)
    {
        aux2 = aux2->next;
    }

    aux2->next = head->inicio;

	time_t now = time(NULL);

 	printf("--------------------------------------------------------------------------------\n");
 	printf("Aeroporto Internacional de Brasília\n");
 	printf("Hora inicial: %s\n", __TIME__);
    printf("Número de Voos: %d\n", num_voos);
    printf("Voos em Aproximação: %d\n", num_aprox);
    printf("Voos em Decolagem: %d\n", num_decol);

    printf("Fila de Pedidos: \n");
    No *l;
    for(l = lista; l != NULL; l = l->next)
    {
        printf("\t\t    [%s - %c -", l->nome, *l->tipo);
        if(*l->tipo == 'D') printf("\tN.A.\t]\n");
        else    printf(" prioridade: %d]\n", l->combustivel);
    }
    free(l);
 	printf("--------------------------------------------------------------------------------\n");
 	printf("LISTAGEM DE EVENTOS:\n\n");

    No* node;
    for(node = lista; node != NULL; node = node->next)
    {
	    if(node->combustivel == 0)
        {
	    	pista = sorteia(1,3,1);
	    	if(pista == 3)
            {
	    		cont++;
	    	}
	    	sos++;

	    	if(sos == 3)
            {
	    		printf("ALERTA GERAL DE DESVIO DE AERONAVE !!\n\n");

                if(cont == 3)
                {
                    printf("Código do voo: %s\n", node->nome);
	    			printf("ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n\n");
                    sos = 1;
	    		}
	    	}
            else
            {
	    		printf("Código do voo: %s\n", node->nome);
 				printf("Status: Aeronave pousou\n");
 				printf("Número da pista: %d\n\n", pista);
	    	}
	    }

	    if(strcmp(node->tipo, "D") == 0)
        {
    		pista = sorteia(1,3,1);
    		printf("Código do voo: %s\n", node->nome);
			printf("Status: Aeronave decolou\n");
			printf("Número da pista: %d\n\n", pista);

            if(pista == 3)
            {
				cont++;
			}
        }
        // else if(strcmp(node->tipo, "P") == 0)
        // {
        //     pista = sorteia(1,2,1);
        //     printf("Código do voo: %s\n", node->nome);
        //     printf("Status: Aeronave pousou\n");
        //     printf("Número da pista: %d\n\n", pista);
        // }
    }

    return 0;
}
