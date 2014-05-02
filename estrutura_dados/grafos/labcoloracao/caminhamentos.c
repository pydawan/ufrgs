#include <stdio.h>
#include <stdlib.h>
#include "caminhamentos.h"
#include "fila.h"


void visita (int vis[max+1], int v)
{
     printf("%d\n",v);
     vis[v]= true;
}

int MaiorGrau(int grafo[max+1][max+1])
{
	int i,j;
	int maior=0;
	int grau=0;
	int grauaux=0;
	for(i=1;i<=max;i++)
    	{
	for(j=1;j<=max;j++)
      	{
		if (grafo[i][j] == 1 || grafo[j][i] == 1)
		{
			grauaux++;
		}
	}
	if (grauaux > grau)
	{
		grau=grauaux;
		maior=i;
	}
	grauaux=0;
	}
	return maior;
}

void ColoreVerticeProfundidade(int grafo[max+1][max+1], int coresvertices[max+1], int vis[max+1], int vertice)
{
	int i,j,adj;
	int corjausada=false;
	//se vertice nao foi colorido|visitado
	if (vis[vertice] == 0)
	{
		 //vamos descobrir se algum vertice adjacente tem cor i 
		 for(i=1;i<=max;i++)
        	 {	   
			corjausada=false;
			//descobrindo os adjacentes
			for(j=1;j<=max;j++)
        		{			   
                		//se vertice j eh adjacente
				if (grafo[vertice][j] == 1 || grafo[j][vertice] == 1)
				{
					//se vertice adjacente ja usa cor i
					if (coresvertices[j] == i)
						corjausada=true; 
				}
			}
			if(corjausada == false)
			{
				//descobrimos a melhor cor pro vertice: i!
				coresvertices[vertice]=i;
				//forcamos a parada do for pq ja achamos melhor cor
				i=max;	
				//Executamos para todos adjacentes recursivamente
				for(adj=1;adj<=max;adj++)
				{
				 	if (grafo[vertice][adj] == 1 || grafo[adj][vertice] == 1)
				 	{ 
						vis[vertice] = 1;
						ColoreVerticeProfundidade(grafo, coresvertices, vis, adj); 
				 	}
				}
			}
			
		}
	}	
}

void PrintaCoresGrafo( int coresvertices[max+1])
{
	int i;
	printf ("Vertice : Cor\n"); 
	for (i=1;i<=max;i++)
		printf ("%d:%d\n",i,coresvertices[i]); 
}

void DFS (int grafo[max+1][max+1], int v, int vis[max+1])
{
    int w;
    visita(vis,v);
    for(w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
      if ((grafo[v][w]== 1) && (vis[w]==false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
         DFS(grafo, w, vis); //chamada recursiva para o vértice adjacente a v
}



void BFS (int grafo[max+1][max+1], int v, int vis[max+1])
{
    int w;
    TipoFila *FV;
    

    visita(vis,v);
    FV = cria_fila();
    FV = insere(FV,v);
    while (!vazia(FV))
    {
       v = remover(&FV);
       for(w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
          if ((grafo[v][w]== 1) && (vis[w]==false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
          {
              FV = insere(FV,w);
              visita(vis,w);
           }
   
    }
}


void Colore(int grafo[max+1][max+1], int vertice, int coresvertices[max+1])
{
	int corjausada,i,j;
		
   //vamos descobrir se algum vertice adjacente tem cor i 
                 for(i=1;i<=max;i++)
                 {    
                        corjausada=false;
                        //descobrindo os adjacentes
                        for(j=1;j<=max;j++)
                        {    
                                //se vertice j eh adjacente
                                if (grafo[vertice][j] == 1 || grafo[j][vertice] == 1)
                                {
                                        //se vertice adjacente ja usa cor i
                                        if (coresvertices[j] == i)
                                                corjausada=true; 
                                }
                        }
                        if(corjausada == false)
                        {
                                //descobrimos a melhor cor pro vertice: i!
                                coresvertices[vertice]=i;
                                //forcamos a parada do for pq ja achamos melhor cor
                                i=max;  
			}	
		}

}


//Pendente
void ColoreVerticeLargura(int grafo[max+1][max+1], int coresvertices[max+1], int vis[max+1], int vertice)
{
	int i,j,adj,w,v;
	int corjausada=false;
        TipoFila *FV;
    	FV = cria_fila();
	Colore(grafo, vertice, coresvertices);
    				FV = insere(FV,vertice);
    				while (!vazia(FV))
    				{
       					v = remover(&FV);
       					for(w = 1; w<=max ; w++)    //percorre os vértices adjacentes a v
			                if (((grafo[v][w]== 1) && (vis[w]==false)) || (grafo[w][v] && vis[w]==false))  
          				{
						FV = insere(FV,w);
              					vis[v]=1;
						Colore(grafo,w,coresvertices);
           				}

				}
}

