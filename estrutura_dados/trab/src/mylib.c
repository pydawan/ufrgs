#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "arvores.h"

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
		// alem do codigo ASC para letras com acento e o '-'  
  		while(linha[cont] >= 'A' && linha[cont] <= 'Z' || linha[cont] >= 'a' && linha[cont] <= 'z' || \
			linha[cont] == -87 ||  linha[cont] == -93 ||  linha[cont] == -77 ||  linha[cont] == -96 || \
			linha[cont] == 45 ||  linha[cont] == -89 || linha[cont] == -61 || linha[cont] == -95 || \
			linha[cont] == -83 ||  linha[cont] == -86 || linha[cont] == -70 || linha[cont] == -75 || \
			linha[cont] == -119 ||  linha[cont] == -125 ||  linha[cont] == -109 ||  linha[cont] == -128 || \
			linha[cont] == -118 ||  linha[cont] == -115 || linha[cont] == -102 || linha[cont] == -107 || \
			linha[cont] == -76 ||  linha[cont] == -108 
			)
		{
			printf("%c", linha[cont]);
			cont++;
		}
		printf("\n");
		cont++;
	} 
	cont=0;
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


pNodoA* DicionarioEmArvore(char arquivo[])
{
  int cont;
  pNodoA* dicarvore;
  dicarvore = NULL;
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
	cont = 0;
	while (linha[cont]!= '\n')
	{
		linha[cont]=tolower(linha[cont]);
		cont++;	
	}	
	dicarvore = InsereArvore(dicarvore, linha);
  }
  if (linha)
    free(linha);
  fclose(f);
	//preFixado(dicarvore);
  return dicarvore;
}


int RevisaOrtografiaTexto(char arquivo[], pNodoA* dicionario)
{
  FILE *f= fopen(arquivo, "r");
  size_t len= 1024; // valor arbitrário
  char *linha= malloc(len);
  int cont=0;
  int cont2=0;
  int l=0;
  char palavra[255];
  pNodoA* nodo;
  pRevisaoA* revisao;
  nodo = NULL;
  revisao = NULL;
  pRevisaoA* ordenado;
  ordenado = NULL;

if (!f)
{
    perror(arquivo);
    exit(1);
}
 while (getline(&linha, &len, f) > 0)
 {
	l++;
	while(linha[cont] != '\n')
	{
		cont2=0;
		//A-Z 65-90 a-z 97-122
		// alem do codigo ASC para letras com acento e o '-'  
  		while(linha[cont] >= 'A' && linha[cont] <= 'Z' || linha[cont] >= 'a' && linha[cont] <= 'z' || \
			linha[cont] == -87 ||  linha[cont] == -93 ||  linha[cont] == -77 ||  linha[cont] == -96 || \
			/*linha[cont] == 45 || hifen*/  linha[cont] == -89 || linha[cont] == -61 || linha[cont] == -95 || \
			linha[cont] == -83 ||  linha[cont] == -86 || linha[cont] == -70 || linha[cont] == -75 || \
			linha[cont] == -119 ||  linha[cont] == -125 ||  linha[cont] == -109 ||  linha[cont] == -128 || \
			linha[cont] == -118 ||  linha[cont] == -115 || linha[cont] == -102 || linha[cont] == -107 || \
			linha[cont] == -76 ||  linha[cont] == -108 
			)
		{
			palavra[cont2]=tolower(linha[cont]);
			cont++;
			cont2++;
		}
		// se iniciamos uma palavra antes de encontrar um caracter q nao esta em palavra, temos uma palavra
		// vamos comparar ela no dicionario
		if (cont2 > 0)
		{
		 palavra[cont2]='\n';
		 cont2++;
		 palavra[cont2]='\0';
		 //puts(palavra);
		 nodo = consultaDic(dicionario, palavra);
		 // Nao estava no dicionario
		 if (nodo == NULL)
		 {
			revisao = InsereRevisao(revisao,palavra, l);
	         }
		}
		cont++;
	} 
	cont=0;
}
  if (linha)
    free(linha);
  fclose(f);
if (dicionario)
	free(dicionario);
  //preFixadoRevisao(revisao);
  //ordenado = OrdenaporOcorrencias(revisao, ordenado, 3);
  printf ("K     |     Ocorrencias     |     Linhas     |     Palavra       \n");
  posFixadoRevisaoOcorrencias(revisao,10);
  return 0;
}

char* Itoa(int value, char* str, int radix)
{
      static char dig[] =
	      "0123456789"
	      "abcdefghijklmnopqrstuvwxyz";
      int n = 0, neg = 0;
      unsigned int v;
      char* p, *q;
      char c;

      if (radix == 10 && value < 0) {
	      value = -value;
	      neg = 1;
      }
      v = value;
      do {
	      str[n++] = dig[v%radix];
	      v /= radix;
      } while (v);
      if (neg)
	      str[n++] = '-';
      str[n] = '\0';
      for (p = str, q = p + n/2; p < q; ++p, --q)
	      c = *p, *p = *q, *q = c;
      return str;
}


long long
timeval_diff(struct timeval *difference,
             struct timeval *end_time,
             struct timeval *start_time
            )
{
  struct timeval temp_diff;

  if(difference==NULL)
  {
    difference=&temp_diff;
  }

  difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
  difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

  /* Using while instead of if below makes the code slightly more robust. */

  while(difference->tv_usec<0)
  {
    difference->tv_usec+=1000000;
    difference->tv_sec -=1;
  }

  return 1000000LL*difference->tv_sec+
                   difference->tv_usec;

} /* timeval_diff() */


