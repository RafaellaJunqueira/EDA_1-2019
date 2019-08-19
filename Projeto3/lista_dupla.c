//Rafaella Junqueira    16/0142628

#include <string.h>
#include "lista_dupla.h"

// void insertion_sort(Lista* l)
// {
//     Lista* aux = head;
//     Lista* aux2;
//
//     for(aux; aux->next != NULL; aux = aux->next)
//     {
//         aux2 = aux->next;
//         if(strcasecmp(aux->nome, aux->next->nome) < 1)
//         {
//             if(head == aux) head = aux2;
//             aux->next = aux2->next;
//             aux2->next->prev = aux2->prev;
//             aux->prev = aux2;
//             aux2->next = aux2->prev;
//             aux2->prev = NULL;
//             free(aux2);
//         }
//     }
//     imprime(l);
// }
Lista *crialista()
{
    _size = 0;
    return NULL;
}
Lista *insere_contato(Lista *l, char nom[101], char tel[100], char ed[101], int cep, char ani[11])
{
    Lista *elem = (Lista*) malloc(sizeof(Lista));
    if(elem == NULL) exit(-1);

    strcpy(elem->nome, nom);
    strcpy(elem->telefone, tel);
    strcpy(elem->endereco, ed);
    elem->CEP = cep;
    strcpy(elem->niver, ani);

    if(l == NULL)
    {
        elem->next = NULL;
        elem->prev = NULL;
        head = elem;
        tail = elem;
        _size++;
        return elem;
    }
    else
    {
        elem->prev = NULL;
        elem->next = head;
        head->prev = elem;
        head = elem;
        _size++;
        return elem;
    }
}
void imprime(Lista *l)
{
    Lista *elem;
    if(_size == 0){
        printf("Lista Vazia!\n");
        return;
    }
    else{
        for(elem = tail; elem != NULL; elem = elem->prev)
        {
            printf("Nome: %s\n", elem->nome);
            printf("Telefone: %s\n", elem->telefone);
            printf("Endereço: %s\n", elem->endereco);
            printf("CEP: %d\n", elem->CEP);
            printf("Nascimento: %s\n", elem->niver);
            printf("\n");
        }
    }
}
void remover_um(Lista *l, char nom[101])
{
    Lista *aux;
    for(aux = head; aux != NULL; aux = aux->next)
    {
        if(strcasecmp(nom, aux->nome) == 0 && aux == head && aux == tail)
        {
            free(aux);
            _size--;
            return;
        }
        if(strcasecmp(aux->nome, nom) == 0 && aux == head)
        {
            head = aux->next;
            aux->next->prev = NULL;
            free(aux);
            _size--;
            return;
        }
        if(strcasecmp(aux->nome, nom) == 0 && aux == tail)
        {
            tail = aux->prev;
            aux->prev->next = NULL;
            free(aux);
            _size--;
            return;
        }
        else
        {
            if(strcasecmp(aux->nome, nom) == 0)
            {
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                free(aux);
                _size--;
                return;
            }
        }
    }
}
void visualizar(Lista *l, char nom[101])
{
    Lista *aux;
    for(aux = head; aux != NULL; aux = aux->next)
    {
        if(strcasecmp(nom, aux->nome) == 0)
        {
            printf("%s\n", aux->nome);
            printf("Telefone: %s\n", aux->telefone);
            printf("Endereço: %s\n", aux->endereco);
            printf("CEP: %d\n", aux->CEP);
            printf("Nascimento: %s\n", aux->niver);
            printf("\n");
        }
    }
}
Lista *grava_arquivo(Lista *l)
{
    FILE *f = fopen("contatos.txt", "r");
    char nome[101], tel[11], end[101], aniver[9];
    int CEP;
    if(f == NULL) exit(-1);
    else
    {
        while(!feof(f))
        {
                fscanf(f, " %[^\n]s", nome);
                fscanf(f, " %[^\n]s", tel);
                fscanf(f, " %[^\n]s", end);
                fscanf(f, "%d", &CEP);
                fscanf(f, " %[^\n]s", aniver);
                l = insere_contato(l, nome, tel, end, CEP, aniver);
        }
    fclose(f);
    }
    return l;
}
int main()
{
    Lista *lista;
    lista = crialista();
    // lista = grava_arquivo(lista);
    lista = insere_contato(lista, "Belva Yelvington", "99799-8331", "Casa das ruas das faculdades da vida", 52501, "25/09/1971");
    lista = insere_contato(lista, "Mirna Halford", "97465-4294", "Franklin", 30721, "15/04/1951");
    lista = insere_contato(lista, "Rodrigo Drews", "92130-3960", "Jockey Hollow", 36301, "04/04/1994");
    lista = insere_contato(lista, "Tarra Casebolt", "96697-6327", "College Rua", 37086, "26/09/1925");
    lista = insere_contato(lista, "Toney Schaffner", "95597-4268", "7596 East", 00046, "13/03/1936");

    int escolha = 0;

    char nom[101], tel[11], ed[101], ani[11];
    int cp;

    while(escolha != 5)
    {
           printf("----------------------------------\n");
           printf("          LISTA DE CONTATOS       \n");
           printf("----------------------------------\n");
           printf(" 1- Inserir novo contato          \n");
           printf(" 2- Remover um contato            \n");
           printf(" 3- Visualizar um contato         \n");
           printf(" 4- Visualizar todos os contatos  \n");
           printf(" 5- Sair                          \n");
           printf("----------------------------------\n");
           printf("Opcao: ");

           scanf("%d", &escolha);
           printf("\n");

        switch(escolha)
        {
           case 1:
           {
               a: printf("Nome: ");
               scanf(" %[^\n]s", nom);
               if(strlen(nom) > 100)
               {
                   printf("Nome muito grande, insira novamente\n");
                   goto a;
               }

               b: printf("Telefone (xxxxx-xxxx): ");
               scanf(" %[^\n]s", tel);
               if(strlen(tel) != 10 || tel[5] != '-')
               {
                   printf("Formato inválido, insira novamente\n");
                   goto b;
               }

               c: printf("Endereço: ");
               scanf(" %[^\n]s", ed);
               if(strlen(ed) > 100)
               {
                   printf("Endereço muito grande, insira novamente\n");
                   goto c;
               }

               printf("CEP: ");
               scanf("%d", &cp);

               e: printf("Data de Nascimento (dd/mm/aaaa): ");
               scanf(" %[^\n]s", ani);
               if(ani[2] != '/' || ani[5] != '/' || strlen(ani) != 10)
               {
                   printf("Formato inválido, insira novamente\n");
                   goto e;
               }
              lista = insere_contato(lista, nom, tel, ed, cp, ani);
               break;
           }
           case 2:
              if(_size == 0)
              {
                  printf("Impossível excluir. A lista já está vazia!\n");
                  break;
              }
              else
              {
                  printf("Digite o contato que deseja excluir: ");
                  char n[101];
                  scanf(" %[^\n]s", n);
                  remover_um(lista, n);
                  break;
              }
           case 3:
           {
               printf("Digite o nome do contato que deseja visualizar: ");
               char n[101];
               scanf("%s", n);
               visualizar(lista, n);
               break;
           }
           case 4:
               // insertion_sort(lista);
               if(lista)
                    imprime(lista);
               else printf("Lista Vazia!\n");
               break;
           case 5:
               exit(1);
           default:
                printf("Digite uma opção válida...\n");
                break;
       }
   }

    return 0;
}
