#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include "Pilha.cpp"


int main ()
{  
    TipoPilha *P1, *P2, *P3, *P4;
    TipoInfo dado;
    
    P1=InicializaPilha(P1);
    P2=InicializaPilha(P2);
    P3=InicializaPilha(P3);
    
    P1 = PushPilha(P1,2);
    P1 = PushPilha(P1,4);
    P1 = PushPilha(P1,6);
    P1 = PushPilha(P1,8);
    P1 = PushPilha(P1,10);
    ImprimirPilha(P1);
    
    if (PopPilha(&P1, &dado))
       printf("elemento %d retirado da pilha\n\n",dado);
    else
       printf("nao foi possivel desempilhar");
       
    if (PopPilha(&P1, &dado))
       printf("elemento %d retirado da pilha\n\n",dado);
    else
       printf("nao foi possivel desempilhar");
       
    if (Vazia(P1))
      printf("a pilha esta vazia\n\n");
    else
       printf("a pilha nao esta vazia\n\n");
       
    ImprimirPilha(P1);
    
    P1 = DestroiPilha(P1);
    
    if (Vazia(P1))
      printf("a pilha esta vazia\n\n");
    else
       printf("a pilha nao esta vazia\n\n");
    
  
    P2 = PushPilha(P2,1);
    P2 = PushPilha(P2,3);
    P2 = PushPilha(P2,4);
    P2 = PushPilha(P2,7);
    
    P3 = PushPilha(P3,2);
    P3 = PushPilha(P3,5);
    P3 = PushPilha(P3,6);
    
    ImprimirPilha(P2);
    ImprimirPilha(P3);
    
    printf("Agora as duas pilhas:\n");
    P4 = OrdenaDuasPilhas(P2,P3);
    ImprimirPilha(P4);
   //system("pause");
}
