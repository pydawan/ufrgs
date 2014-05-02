#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvores.h"

pNodoA* InsereArvore(pNodoA *a, char ch[100])
{
     if (a == NULL)
     {
         a =  (pNodoA*) malloc(sizeof(pNodoA));
	strcpy(a->info,ch);
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else 
	{     
	if (strcmp(ch,a->info) < 0)
          {   
	         a->esq = InsereArvore(a->esq,ch);
          }
	  else if (strcmp(ch,a->info) > 0)
          {
              a->dir = InsereArvore(a->dir,ch);          
	  }
     return a;
	}
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
	  puts(a->info);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->esq);
          printf("%s\n",a->info);
          Central(a->dir);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%s\n",a->info);
      }
}

pNodoA* consultaABP(pNodoA *a, char chave[100]) {
 
    while (a!=NULL){
          if (a->info == chave )
             return a; //achou então retorna o ponteiro para o nodo
          else
            if (a->info > chave)
               a = a->esq;
            else
               a = a->dir;
            }
            return NULL; //se não achou
}

pNodoA* consultaABP2(pNodoA *a, char chave[100]) {
    if (a!=NULL) {
          

       if (a->info == chave)
         return a;
       else 
           if (a->info > chave)
                return consultaABP2(a->esq,chave);
            if (a->info < chave)
                return consultaABP2(a->dir,chave);
                
            else return a;
       }
       else return NULL;
}

int Altura (pNodoA *a)
{
int Alt_Esq, Alt_Dir;
if (a == NULL)
return 0;
else
{
Alt_Esq = Altura (a->esq);
Alt_Dir = Altura (a->dir);
if (Alt_Esq > Alt_Dir)
return (1 + Alt_Esq);
else
return (1 + Alt_Dir);
}
}

int FatorBalanceamento(pNodoA *a)
{
return (Altura(a->esq) - Altura(a->dir));
}

int MaiorBalanceamento(pNodoA *a)
{
	int Bal_Esq, Bal_Dir;
	if (a == NULL)
	{
		a->FB=0;
	}
	else
	{
		a->FB=FatorBalanceamento(a);
		if (a->esq != NULL && a->dir != NULL)
		{
			Bal_Esq=MaiorBalanceamento(a->esq);
			Bal_Dir=MaiorBalanceamento(a->dir);
		}
		else
		{
			Bal_Esq=0;
			Bal_Dir=0;
		}

		if (abs(a->FB) > abs(Bal_Esq))
		{
			if (abs(a->FB) > abs(Bal_Dir))
				return a->FB;
			else
				return Bal_Dir;
		}
		else if (abs(Bal_Esq) > abs(Bal_Dir))
			return Bal_Esq;
		else
			return Bal_Dir;
	}
		return a->FB;
}


pNodoA* consultaDic(pNodoA *a, char chave[100]) {
 
    while (a!=NULL){
	  if (strcmp(chave,a->info) == 0)
             return a; //achou então retorna o ponteiro para o nodo
          else
          {
	   //printf("comparando %d  - %d com %d : %c %c \n",strcmp(chave,a->info) ,strlen(chave), strlen(a->info),a->info[0], a->info[1]);
	   //puts(chave);
	   //puts(a->info); 
	    if (strcmp(chave,a->info) < 0)
               a = a->esq;
            else
               a = a->dir;
          }
	  }
            return NULL; //se não achou
}


pRevisaoA* InsereRevisao(pRevisaoA *a, char ch[100], int linha)
{
     char linhastr[255];
     if (a == NULL)
     {
         a =  (pRevisaoA*) malloc(sizeof(pRevisaoA));
	strcpy(a->info,ch);
	strcat(a->linhas, Itoa(linha, linhastr, 10));
	a->ocorrencias=a->ocorrencias + 1;
         a->esq = NULL;
         a->dir = NULL;
	//puts(ch);
	//puts(a->linhas);
	//printf("ocorrencias: %d\n####################################\n",a->ocorrencias);
	//printf("INSERINDO: %s em %p \n",a->info, a);
         return a;
     }
     else 
	{     
	if (strcmp(ch,a->info) < 0)
          {   
	   	//printf("comparando %d  - %s com %s em %p \n",strcmp(ch,a->info) ,ch, a->info, a);
		//printf("Inserir: ");   
		//puts(ch);
	   	//puts(a->info);
		//printf("dir: %s |",a->dir->info); 
		//printf("esq: %s\n",a->esq->info); 
	  	//printf("####################################################\n\n");
	         a->esq = InsereRevisao(a->esq,ch,linha);
          }
	else
	{
		if (strcmp(ch,a->info) > 0)
          	{
	   		//printf("comparando %d  - %s com %s em %p \n",strcmp(ch,a->info) ,ch, a->info, a);
			//printf("Inserir: ");   
			//puts(ch);
	   		//puts(a->info); 
			//printf("dir: %s |",a->dir->info); 
			//printf("esq: %s\n",a->esq->info); 
	  		//printf("####################################################\n\n");
              		a->dir = InsereRevisao(a->dir,ch,linha);
		}
	     	else // entao eh igual.
		{
	   		//printf("comparando %d  - %s com %s em %p \n",strcmp(ch,a->info) ,ch, a->info, a);
			//printf("Inserir: ");   
	   		//puts(ch);
	   		//puts(a->info); 
			//printf("dir: %s |",a->dir->info); 
			//printf("esq: %s\n",a->esq->info); 
	  		//printf("####################################################\n\n");
			strcat(a->linhas,",");
			strcat(a->linhas, Itoa(linha, linhastr, 10));
			a->ocorrencias=a->ocorrencias + 1;
			//puts(a->linhas);
			//printf("ocorrencias: %d\n####################################\n",a->ocorrencias);
			
		}			          
        return a;
	}
	}
}



pRevisaoA* OrdenaporOcorrencias(pRevisaoA *a, pRevisaoA *aux, int k)
{
     printf ("executei\n"); 	
     if (a!= NULL )
     {
	if (aux==NULL)
	{
         aux =  (pRevisaoA*) malloc(sizeof(pRevisaoA));
	 strcpy(aux->info,a->info);
	 strcat(aux->linhas, a->linhas);
	 aux->ocorrencias=a->ocorrencias;
         aux->esq = NULL;
         aux->dir = NULL;
	 printf ("cadastrei %d - %s\n", k, aux->info);
	 k--;
		if (a->esq != NULL)
			aux = OrdenaporOcorrencias(a->esq, aux, k);
		if (a->dir != NULL)
			aux = OrdenaporOcorrencias(a->dir, aux, k);
         return aux;
	}
	else
	{
		if (a->ocorrencias < aux->ocorrencias)	
		{
				
			aux->esq = OrdenaporOcorrencias(a, aux->esq, k);
		}
		else
		{
			aux->dir = OrdenaporOcorrencias(a, aux->dir, k);
		}
        return aux;
        }
      }
        return NULL;
}


void preFixadoRevisao(pRevisaoA *a)
{
     if (a!= NULL)
     {
	  printf("Palavra: %s Ocorrencias: %d \n Linhas: %s",a->info,a->ocorrencias,a->linhas);
	  //printf("Palavra: %s Ocorrencias: %d ",a->info,a->ocorrencias);
	  printf("\n\n####################################################\n\n");
	  
          preFixadoRevisao(a->esq);
          preFixadoRevisao(a->dir);
	}
}


void posFixadoRevisaoOcorrencias(pRevisaoA *a, int k)
{
     if (k > 0 && a!= NULL)
     {	
	  k--;
          posFixadoRevisaoOcorrencias(a->dir, k);
	  k--;
          posFixadoRevisaoOcorrencias(a->esq, k);
	  k--;
     	  printf("%d          %d                    %s          %s",k,a->ocorrencias,a->linhas,a->info);
     }
}
