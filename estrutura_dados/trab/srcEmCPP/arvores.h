struct TNodoA{
        int info;
        int FB;
        struct TNodoA *esq;        
        struct TNodoA *dir;        
};
typedef struct TNodoA pNodoA;

pNodoA* InsereArvore(pNodoA *a, int ch);
void preFixado(pNodoA *a);
void posFixado(pNodoA *a);
void Central(pNodoA *a);
pNodoA* consultaABP(pNodoA *a, int chave);
pNodoA* consultaABP2(pNodoA *a, int chave);
