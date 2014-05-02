#include <stdio.h>
#include <stdlib.h>
#define max 6
#define true 1
#define false 0

void Colore(int grafo[max+1][max+1], int vertice, int coresvertices[max+1]);
void ColoreVerticeProfundidade(int grafo[max+1][max+1], int coresvertices[max+1], int vis[max+1], int vertice);
void PrintaCoresGrafo(int coresvertices[max+1]);
int MaiorGrau(int grafo[max+1][max+1]);
void DFS (int grafo[max+1][max+1], int v,   int vis[max+1]);
void BFS (int grafo[max+1][max+1], int v,   int vis[max+1]);
