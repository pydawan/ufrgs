#define _GNU_SOURCE // necessário porque getline() é extensão GNU

int LeLinhaArquivo(char arquivo[]);
int LePalavraArquivo(char arquivo[]);
long long
timeval_diff(struct timeval *difference,
             struct timeval *end_time,
             struct timeval *start_time
            );



struct ResultadoA{ //serah uma arvore splay
        char info[100];
        int ocorrencias;
        char linhas[255]; //vou usar strcat para ir concatenando linhas q tem ocorrencia        
        struct ResultadoA *esq;        
        struct ResultadoA *dir;        
};
typedef struct ResultadoA RESULTADOA;
