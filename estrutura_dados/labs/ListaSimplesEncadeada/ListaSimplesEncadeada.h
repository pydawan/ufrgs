struct Produto {
       int codigo;
       char nome[20];
       float preco;
}typedef Produto;

struct PtProduto {
       Produto prod;
       PtProduto* prox;
}typedef PtProduto;

PtProduto* InicializaLista(void);
PtProduto* InsereProduto (PtProduto* p, Produto dados);
void Imprime(PtProduto* p);
