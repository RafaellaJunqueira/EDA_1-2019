#include <stdio.h>

int fneuronio(int *ent, int *pes, int limite)
{
    int somap = 0;
    for(int i = 0; i < 10; i++)
    {
        somap += (*(ent + i))* (*(pes + i));
    }
    if(somap >= limite) return 1;
    else return 0;
}

int main()
{
    int entradas[10], pesos[10], T;
    int *p1 = entradas, *p2 = pesos;

// leitura do vetor de entrada
    for(int i = 0; i < 10; i++)
    {
        printf("Digite o valor de entrada de posição %d: ", i);
        scanf("%d", &entradas[i]);
        if(i + 1 == 10) printf("\n");
    }

// leitura do vetor de pesos
    for(int i = 0; i < 10; i++)
    {
        printf("Digite o valor do peso %d: ", i);
        scanf("%d", &pesos[i]);
        if(i + 1 == 10) printf("\n");
    }

// leitura do limite T
    printf("Digite o valor do limiar T: ");
    scanf("%d", &T);

// Chamar a função de multiplicações
    if(fneuronio(p1, p2, T)) printf("Neurônio ativado!\n");
    else printf("Neurônio inibido!\n");

    return 0;
}
