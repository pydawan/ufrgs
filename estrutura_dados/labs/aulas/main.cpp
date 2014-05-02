#include <stdio.h>
#include <stdlib.h>
#include "LSE_Ord.h"

int main(void)
{
    TipoInfoNo dados;
    char cont;
    
    TipoPtNo* l;
    l = cria_lista();
    do
    {
        printf("Codigo: "); scanf("%d",&dados.codigo);
        printf("Nome: "); scanf("%s",dados.nome);
        printf("Preco: "); scanf("%f",&dados.preco);
        l = insere_ord(l, dados);
        printf("Continua? \n"); 
        fflush(stdin);
        cont = getchar(); 
    }while (cont!='n');
    imprime(l);
    system("pause");
}
