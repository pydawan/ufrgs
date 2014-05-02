#include "caminhamentos.h"
#include "fila.h"

int main()
{
  int i,j;
  int grafo[max+1][max+1];
  int vis[max+1];
  int coresvertices[max+1];
  
  //para inicializar o gráfo com 0
  for(i=1;i<=max;i++)
    for(j=1;j<=max;j++)
      grafo[i][j]=0;  

 for (i=1;i<=max;i++)
        vis[i]=false; //inicializando vetor de vertices visitados

 for (i=1;i<=max;i++)
        coresvertices[i]=false; //inicializando vetor das cores dos vertices

    grafo[1][2]=1;
    grafo[1][6]=1;
    grafo[2][3]=1;
    grafo[2][4]=1;
    grafo[3][4]=1;
    grafo[3][5]=1;
    grafo[4][5]=1;
    grafo[4][6]=1;
    grafo[5][6]=1;


   printf("COlore em profundidade:\n");
   ColoreVerticeProfundidade(grafo, coresvertices, vis, MaiorGrau(grafo));
   PrintaCoresGrafo(coresvertices);
	 
    for (i=1;i<=max;i++)
        vis[i]=false; //inicializando vetor de vertices visitados
    for (i=1;i<=max;i++)
        coresvertices[i]=false; //inicializando vetor das cores dos vertices


   printf("COlore em largura:\n");
   ColoreVerticeLargura(grafo, coresvertices, vis, MaiorGrau(grafo));
   PrintaCoresGrafo(coresvertices);
 
}
