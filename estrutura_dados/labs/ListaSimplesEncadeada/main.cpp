#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "ListaSimplesEncadeada.h"


int main(void)
{
	PtProduto* lista_produtos;
	Produto dados;
	char cont;
	
	lista_produtos = InicializaLista();
	printf("Endereco da lista: %p\n", lista_produtos);
	
	//insercao de dados por parte do usuario
	do
    {
        printf("Codigo: "); scanf("%d",&dados.codigo);
        printf("Nome: "); scanf("%s",dados.nome);
        printf("Preco: "); scanf("%f",&dados.preco);
        lista_produtos = InsereProduto(lista_produtos, dados);
        printf("Continua? \n"); 
        //fflush(stdin);
        __fpurge(stdin); 
        cont = getchar(); 
    }while (cont!='n');
	
	Imprime(lista_produtos);
	
	return 0;
}
