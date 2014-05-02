#include <stdio.h>
#include <stdlib.h>
#include "abp.h"
#include "abp.cpp"

int main()
{

	pNodoA *arvoreteste, *arvoreteste2, *arvoreteste3, *arvoreteste4;
	arvoreteste = NULL;
	arvoreteste2 = NULL;
	arvoreteste3 = NULL;
	arvoreteste4 = NULL;

	arvoreteste = InsereArvore(arvoreteste, 42);
	arvoreteste = InsereArvore(arvoreteste, 15);
	arvoreteste = InsereArvore(arvoreteste, 88);
	arvoreteste = InsereArvore(arvoreteste, 6);
	arvoreteste = InsereArvore(arvoreteste, 27);
	arvoreteste = InsereArvore(arvoreteste, 20);
	arvoreteste = InsereArvore(arvoreteste, 63);
	arvoreteste = InsereArvore(arvoreteste, 94);
	arvoreteste = InsereArvore(arvoreteste, 57);
	arvoreteste = InsereArvore(arvoreteste, 71);

	
	arvoreteste2 = InsereArvore(arvoreteste2, 42);
	arvoreteste2 = InsereArvore(arvoreteste2, 15);
	arvoreteste2 = InsereArvore(arvoreteste2, 27);
	arvoreteste2 = InsereArvore(arvoreteste2, 20);


	arvoreteste3 = InsereArvore(arvoreteste3, 42);
	arvoreteste3 = InsereArvore(arvoreteste3, 15);
	arvoreteste3 = InsereArvore(arvoreteste3, 88);
	arvoreteste3 = InsereArvore(arvoreteste3, 20);
	arvoreteste3 = InsereArvore(arvoreteste3, 27);
	arvoreteste3 = InsereArvore(arvoreteste3, 63);
	arvoreteste3 = InsereArvore(arvoreteste3, 57);
	arvoreteste3 = InsereArvore(arvoreteste3, 71);

	preFixado(arvoreteste);
	printf("Fator balanceamento: %d\n",MaiorBalanceamento(arvoreteste));
	preFixado(arvoreteste2);
	printf("Fator balanceamento: %d\n",MaiorBalanceamento(arvoreteste2));
	preFixado(arvoreteste3);
	printf("Fator balanceamento: %d\n",MaiorBalanceamento(arvoreteste3));

	
	
}
