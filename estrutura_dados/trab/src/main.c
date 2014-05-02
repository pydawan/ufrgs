#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "grafos.h"
#include "arvores.h"
#include "mylib.h"
#include <time.h>

int main(char texto[], char dicionario[])
{
	char frase[255];
	pNodoA* dicarvore;
	dicarvore = NULL;

	//estruturas necessarias para calcular tempo
	struct timeval earlier;
	struct timeval later;
	struct timeval interval;

	gettimeofday(&earlier,NULL);
	dicarvore = DicionarioEmArvore("../txt/br.dic");
	gettimeofday(&later,NULL);
	timeval_diff(&interval,&later,&earlier);
	printf("Botar o dicionario em arvore durou: %ld segundo(s) e  %ld microsegundos.\n",interval.tv_sec,interval.tv_usec);

	gettimeofday(&earlier,NULL);
	RevisaOrtografiaTexto("../txt/texto1.txt", dicarvore);
	gettimeofday(&later,NULL);
	timeval_diff(&interval,&later,&earlier);
	printf("Fazer a revisao ortografica durou: %ld segundo(s) e  %ld microsegundos.\n",interval.tv_sec,interval.tv_usec);
	//LeLinhaArquivo("../txt/br.dic");
	//DicionarioEmArvore("../txt/br.dic");

	return 0;
}
