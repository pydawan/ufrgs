#include <stdio.h>
#include <stdlib.h>
#include "ListaSimplesEncadeada.h"

PtProduto* InicializaLista(void)
{
	return NULL;
}

PtProduto* InsereProduto (PtProduto* p, Produto dados)
{
	PtProduto *aux,*novo,*ant,*ret; 

	novo = (PtProduto*) malloc(sizeof(PtProduto));
	novo->prod = dados;
	novo->prox= NULL;

	//lista vazia, caso trivial
	if ( p == NULL )
	{
		ret = novo;
	}
	else
	{
		aux = p;
		while ( aux != NULL && aux->prod.codigo > novo->prod.codigo )
		{
			ant=aux;
			aux = aux->prox;
		}
		//chegou no fim da lista, sera o ultimo elemento
		if ( aux == NULL)
		{
			ant->prox=novo;
		}
		//insercao no meio ou no inicio da lista
		else
		{
			novo->prox=aux->prox;
			aux->prox=novo;
		} 	
		ret = p;
	}
	return ret;
}

void Imprime(PtProduto* p)
{
	//lista vazia, caso trivial
	if ( p == NULL )
	{
		printf("lista vazia\n");
	}
	else
	{
		while (p != NULL)
		{
			printf ("\nCodigo: %d\n",p->prod.codigo);
			printf ("Nome: %s\n",p->prod.nome);
			printf ("Preco: %f\n",p->prod.preco);
			p = p->prox;
		}
	}
}
