/*analisa um arq txt qualquer  
Atualização de resultados e estatísticas dos jogos, após a conclusão de um jogo, incluindo
atualizações dos arquivos jogadores.dat, jogos.dat e ranking.txt.*/
//le o out.txt e converte pra numeros, vetor d ateh 20 jogos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *arq_jog;

void converte_numeros(FILE *arq_jog, char nome_arquivo[]);

int main()
{
    converte_numeros(arq_jog ,"out.txt");
    system("pause>NULL");
    return 0;

}


void converte_numeros(FILE *arq_jog, char nome_arquivo[100])
{
    int i=0, NumeroEmInt[19], j=0;
    char carac, NumeroEmCaracter[]={'0', '0', '0'};
    if((arq_jog = fopen(nome_arquivo, "r")) == NULL)
            printf("erro de abertura");
    else
    {  
       while((carac=getc(arq_jog)) != EOF)
       {
           
           do
           {
              NumeroEmCaracter[0] = NumeroEmCaracter[1];
              NumeroEmCaracter[1] = NumeroEmCaracter[2];
              NumeroEmCaracter[2]=carac;//começa a ler pelas unidades
              i++;
              carac=getc(arq_jog);
           } while(carac != '*');
           
           NumeroEmInt[j] = atoi(NumeroEmCaracter);
           printf("%d\n",NumeroEmInt[j]);
           NumeroEmCaracter[0]='0';
           NumeroEmCaracter[1]='0';
           NumeroEmCaracter[2]='0';
           i = 0;
           j++;
     
       }
     
       fclose(arq_jog);
     }
   
}
