#include <stdio.h>
#include <stdlib.h>

//função que inicializa a pilha retornando NULL
TipoPilha* InicializaPilha (TipoPilha *Topo)
{
    return NULL;
}


//função que testa se a pilha está vazia (1) ou não (0)
int Vazia (TipoPilha *Topo)
{
    if (Topo==NULL)
       return 1;
    else
       return 0;
}

//função que mostra todos os elementos da pilha
void ImprimirPilha (TipoPilha *Topo)
{
     TipoPilha *ptaux;
     
     if (Topo != NULL)
     {
        puts("---Imprimindo pilha---");      
        for (ptaux=Topo; ptaux!=NULL; ptaux=ptaux->elo)
            printf("%d\n",ptaux->dado);
        puts("-------Fim pilha------");
     }
     else
       puts("Pilha vazia");

}

//função que insere na pilha apontada por Topo o dado recebido como parêmetro. 
//A pilha alterada é retornada ao programa principal
TipoPilha* PushPilha (TipoPilha *Topo, TipoInfo Dado)
{
       TipoPilha *novo; //novo elemento
       TipoPilha *ptaux = Topo; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (TipoPilha*) malloc(sizeof(TipoPilha));
       novo->elo = NULL;
       
       /*insere a informação no novo nodo*/
       novo->dado = Dado;
       
       /*encaeia o elemento*/
       novo->elo = Topo;
       Topo = novo;
       return Topo;
}

//função que remove o elemento do topo da pilha
//o dado removido é retornado no parâmetro Dado
//a função retorna 1 caso tenha conseguido remover e 0 caso contrário
int PopPilha (TipoPilha **Topo, TipoInfo *Dado) //retorna 1 se exclui e zero se não exclui
{
   TipoPilha* ptaux;
   
   if (*Topo == NULL)
     return 0;   //não tem nada na pilha 
   else
   {
        *Dado = (*Topo)->dado;     // devolve o valor do topo 
        ptaux = *Topo;          //guarda o endereço do topo 
        *Topo = (*Topo)->elo;     //o próximo passa a ser o topo 
        free(ptaux);           //libera o que estava no topo 
        ptaux=NULL;
        return 1;    
   }
}
//função devolve o dado que está no topo da pilha
TipoInfo ConsultaPilha (TipoPilha *Topo)
{
 if (Topo==NULL)
   return 0;
 else
   return Topo->dado;
     
}

//função que libera todas as posições de memória ocupadas pela pilha retornando NULL
TipoPilha* DestroiPilha (TipoPilha *Topo)
{
        TipoPilha *ptaux;
        while (Topo != NULL)
        {
          ptaux = Topo;          //guarda o endereço do topo 
          Topo = Topo->elo;     //o próximo passa a ser o topo 
          free(ptaux);           //libera o que estava no topo   
        }  
        return NULL;
}
          
TipoPilha* OrdenaDuasPilhas(TipoPilha *P2, TipoPilha *P3)
{

  TipoPilha  *Pant, *Pnova, *Paux2, *Paux3;
  Paux2 = P2;
  Paux3 = P3;

  while (Paux3->elo != NULL)
  {
    while(Paux3->dado <= Paux2->dado)
    {
      Pant = Paux2;
      Paux2 = Paux2->elo;
    }
    Pnova = (TipoPilha*) malloc(sizeof(TipoPilha));
    Pnova->elo = Paux2;
    Pnova->dado = Paux3->dado;
    Pant->elo = Pnova;
    Paux3 = Paux3->elo;  
  }
  
  if (Paux3->dado > Paux2->dado)
  {
  Pnova = (TipoPilha*) malloc(sizeof(TipoPilha));
  Pnova->elo = Paux2;
  Pnova->dado = Paux3->dado;
  }
  else
  {
  Pnova = (TipoPilha*) malloc(sizeof(TipoPilha));
  Pnova->dado = Paux3->dado;
  Paux2->elo = Pnova;
  Pnova->elo = NULL;
  }
  return P2;
}


