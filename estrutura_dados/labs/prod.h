#include<stdlib.h>
#include<stdio.h>
#define MAX 10

typedef struct produto{
       int codigo;
       char nome[];
       float preco;
       }TipoProd;

struct TipoPtNo{
       TipoProd prod;
       TipoPtNo* prox;
       };
       
TipoPtNo* inicializa ();
TipoPtNo* insere (TipoPtNo* t, TipoProd);
void imprime(TipoPtNo* ptLista);   
       
