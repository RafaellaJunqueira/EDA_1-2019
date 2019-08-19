#include <stdio.h>

void hanoi(int discos, char orig, char dest, char aux){
    if(discos == 1){
        printf("\t|*| Mova o disco 1 da torre '%c' para torre '%c'\n",orig,dest);
    }else{
	    hanoi((discos-1),orig,aux,dest);
    	printf("\t|*| Mova o disco %d da torre '%c' para a torre '%c'\n", discos, orig, dest);
	    hanoi(discos-1,aux, dest, orig);
    }
}

int main(){
    int discos;

    printf("Digite a quantidade de discos: ");
    scanf("%d",&discos);
    printf("\nTorre de Hanoi com %d discos:\n\n",discos);
    hanoi(discos,'A','C','B');
    printf("\n");

    return 0;
}
