#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>


// Nossas bibliotecas
#include <e:\PainelControleJogos\constantes.h>
#include <e:\PainelControleJogos\estruturas.h>
#include <e:\PainelControleJogos\funcoes.h>



int main()
{
    int sair=0;
        
    
    do
    {
    sair = MenuPrincipal(&logado);
    } while( sair == 0);
    
	//AtualizaRanking("Germano","Musical",73);
    //system("pause");    
    return 0;
}
