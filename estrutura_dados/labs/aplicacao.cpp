#include "prod.h"

int main(){
    
    TipoPtNo* produto;
    TipoProd produto2;
    
    produto = inicializa();
    
    printf("\nCodigo");
    scanf("%d", &produto2.codigo);
    fflush(stdin);
    printf("\nNome ");
    fgets(produto2.nome,50, stdin);   
    printf("\nPreco:");
    scanf("%f", &produto2.preco);
    
    produto = insere(produto, produto2);
    imprime(produto);
    
    system("pause");
    return 0;
}
