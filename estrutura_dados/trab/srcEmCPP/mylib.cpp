#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int LeLinhaArquivo(char arquivo[])
{
  FILE *f= fopen(arquivo, "r");
  size_t len= 100; // valor arbitrário
  char *linha= malloc(len);

if (!f)
{
    perror(arquivo);
    exit(1);
}
  while (getline(&linha, &len, f) > 0)
  {
    printf("%s", linha);
  }
  if (linha)
    free(linha);
  fclose(f);
  return 0;
}

int LePalavraArquivo(char arquivo[])
{
  FILE *f= fopen(arquivo, "r");
  size_t len= 1024; // valor arbitrário
  char *linha= malloc(len);
  int cont=0;
  char palavra[255];


if (!f)
{
    perror(arquivo);
    exit(1);
}
 while (getline(&linha, &len, f) > 0)
 {
	while(linha[cont] != '\n')
	{
		//A-Z 65-90 a-z 97-122
  		while(linha[cont] >= 'A' && linha[cont] <= 'Z' || linha[cont] >= 'a' && linha[cont] <= 'z')
		{
			printf("%c", linha[cont]);
			cont++;
		}
		printf("\n** %c **\n",linha[cont]);
		cont++;
	} 
}
  if (linha)
    free(linha);
  fclose(f);
  return 0;
}


void PrintaASC(void)
{
	int cont=0;
	char asc='a';
	while (cont < 255)
	{
		printf ("%d - %c\n",asc,asc);
		cont++;
		asc++;
	}
}
