#include <stdio.h>
#include <conio.h>
#include <stdlib.h>  //necessaria para o malloc
#include "LSE_Ord.h"



TipoPtNo* cria_lista(void)
{
       return NULL;
}

TipoPtNo* insere_ord (TipoPtNo* l, TipoInfoNo dados)
{
       TipoPtNo *novo; //novo elemento
       TipoPtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
       TipoPtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));
       
       /*insere a informação no novo nodo*/
       novo->info = dados;
       
       
       /*procurando a posição de inserção*/
       while ((ptaux!=NULL) && (ptaux->info.codigo < dados.codigo))
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }
       
       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
             //  puts("inserindo primeiro");
               novo->prox = l;
               l = novo;
       }
       else /*elemento inserido no meio da lista*/
       {
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return l;
}
void imprime(TipoPtNo* l)
{
     TipoPtNo* ptaux;
     for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
         printf("Cod = %d Nome = %s Preco= %4.2f \n",ptaux->info.codigo,ptaux->info.nome, ptaux->info.preco);
}         
