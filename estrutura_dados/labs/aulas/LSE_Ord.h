struct s_TipoInfoNo{
       int codigo;
       char nome[20];
       float preco;
       };
typedef struct s_TipoInfoNo TipoInfoNo;


struct s_TipoPtNo{
       TipoInfoNo info;
       s_TipoPtNo* prox;
       };

typedef struct s_TipoPtNo TipoPtNo;

TipoPtNo* cria_lista(void);
TipoPtNo* insere_ord (TipoPtNo* l, TipoInfoNo dados);
void imprime(TipoPtNo* l);
