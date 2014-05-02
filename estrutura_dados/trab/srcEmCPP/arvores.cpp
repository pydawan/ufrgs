#include <stdio.h>
#include <math.h>
#include "arvores.h"

pNodoA* InsereArvore(pNodoA *a, int ch)
{
     if (a == NULL)
     {
         a =  (pNodoA*) malloc(sizeof(pNodoA));
         a->info = ch;
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else 
          if (ch < a->info)
              a->esq = InsereArvore(a->esq,ch);
          else if (ch > a->info)
              a->dir = InsereArvore(a->dir,ch);          
     return a;
}

void preFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%d\n",a->info);
          preFixado(a->esq);
          preFixado(a->dir);
      }
}

void Central(pNodoA *a)
{
     if (a!= NULL)
     {
          Central(a->esq);
          printf("%c\n",a->info);
          Central(a->dir);
      }
}

void posFixado(pNodoA *a)
{
     if (a!= NULL)
     {
          posFixado(a->esq);
          posFixado(a->dir);
          printf("%c\n",a->info);
      }
}

pNodoA* consultaABP(pNodoA *a, int chave) {
 
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

pNodoA* consultaABP2(pNodoA *a, int chave) {
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
