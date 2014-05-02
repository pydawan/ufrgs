struct TNodoA{
        char info[100];
        int FB;
        struct TNodoA *esq;        
        struct TNodoA *dir;        
};
typedef struct TNodoA pNodoA;


struct TRevisaoA{
        char info[23];
	int ocorrencias;
        char linhas[50];
        struct TRevisaoA *esq;        
        struct TRevisaoA *dir;        
};
typedef struct TRevisaoA pRevisaoA;

pNodoA* InsereArvore(pNodoA *a, char ch[100]);
pRevisaoA* InsereRevisao(pRevisaoA *a, char ch[100], int linha);
void preFixadoRevisao(pRevisaoA *a);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaDic(pNodoA *a, char chave[100]);
pNodoA* consultaABP(pNodoA *a, char chave[100]);
pNodoA* consultaABP2(pNodoA *a, char chave[100]);
