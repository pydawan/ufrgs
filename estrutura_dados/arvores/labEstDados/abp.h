struct TNodoA{
        int info;
        int FB;
        struct TNodoA *esq;        
        struct TNodoA *dir;        
};

typedef struct TNodoA pNodoA;

pNodoA* InsereArvore(pNodoA *a, char ch);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, char chave);
pNodoA* consultaABP2(pNodoA *a, char chave);
