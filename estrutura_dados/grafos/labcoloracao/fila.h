
struct TipoFila{
       int info;
       struct TipoFila *prox;
       };
typedef struct TipoFila TipoFila;

TipoFila* cria_fila(void);
TipoFila* insere (TipoFila *l, int dado);
int vazia (TipoFila* l);
int remover(TipoFila **l);
void imprime(TipoFila* l);


