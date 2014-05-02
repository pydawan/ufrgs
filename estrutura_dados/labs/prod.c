#include<stdlib.h>
#include<stdio.h>
#include "prod.h"


TipoPtNo* inicializa (){
    return NULL;
     
}


TipoPtNo* insere (TipoPtNo* t, TipoProd p){
     
     TipoPtNo* aux;
     TipoPtNo* ant;
     TipoPtNo* Novo;
     
     
     Novo = (TipoPtNo*) malloc(sizeof(TipoPtNo));
     Novo->prod = p;
        //lista vazia
        if ( t == NULL ){
           t->prod = p;
           t->prox = NULL;
           return t;
        }
        aux = t;     
        while ( aux !=NULL && p.codigo< aux->prod.codigo)
        {
              ant = aux;
              aux = aux->prox;
              }
        //insere no final da lista
        if ( aux == NULL ){
           ant->prox = Novo;
           Novo->prox = NULL;
           return t;
        }
        else
        {
        ant->prox = Novo;
        Novo->prox = aux;
        }
        
          


}     

void imprime(TipoPtNo* ptLista)
{
     TipoPtNo* ptaux;
     if (ptLista == NULL)
        puts("lista vazia");
     else
         for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->prox)
             printf("Codigo = %d Nome = %s Preco = %f\n",
             ptaux->prod.codigo,
             ptaux->prod.nome,
             ptaux->prod.preco);     
}

