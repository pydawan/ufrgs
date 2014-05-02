#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"


int main ()
{  
    TipoPilha *P1, *P2, *P_ordenada;
    TipoInfo dado;
    
    P1=InicializaPilha(P1);
    
    P1 = PushPilha(P1,2);
    P1 = PushPilha(P1,5);
    P1 = PushPilha(P1,6);
    
    ImprimirPilha(P1);
    
    P2=InicializaPilha(P2);
    P2 = PushPilha(P2,1);
    P2 = PushPilha(P2,3);
    P2 = PushPilha(P2,4);
    P2 = PushPilha(P2,7);
  
    ImprimirPilha(P2);
    
    P_ordenada = ordena(P1,P2);
  
    ImprimirPilha(P_ordenada);
          
    system("pause");
}
