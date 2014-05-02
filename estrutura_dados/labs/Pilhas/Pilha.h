typedef int TipoInfo;

//define a estrutura de uma pilha de inteiros
struct TPtPilha{
        TipoInfo dado;
        struct TPtPilha *elo;        
};
typedef struct TPtPilha TipoPilha;


TipoPilha* InicializaPilha (TipoPilha *Topo);
int Vazia (TipoPilha *Topo);
void ImprimirPilha (TipoPilha *Topo);
TipoPilha* PushPilha (TipoPilha *Topo, TipoInfo Dado);
int PopPilha (TipoPilha **Topo, TipoInfo *Dado);
TipoInfo ConsultaPilha (TipoPilha *Topo);
TipoPilha* DestroiPilha (TipoPilha *Topo);
