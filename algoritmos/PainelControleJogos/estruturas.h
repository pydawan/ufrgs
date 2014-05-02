struct tipo_jogador
{
   int id;                             //identificador do jogador (pode ter check-digit)
   char nome[MAXNOMEJOGADOR];                    //nome do usuário – jogador
   char senha[MAXSENHAJOGADOR];                     //senha para fazer login
   int jogadas;                       //numero de vezes que jogou os jogos- acumulado
   int ultimo_reg_res;                //ponteiro para último registro deste jogador em resultados.dat
   char ativo;                         // se s, jogador ativo, se n jogador inativo
} typedef JOGADOR;

 struct tipo_jogo
{
     int cod;             //código do jogo, atribuído seqüencialmente
     char jogo[MAXNOMEJOGO];       //nome do jogo
     char pasta[MAXPASTAJOGO];       //nome da pasta em que se encontram os dados do jogo
     char exec[MAXEXECJOGO];       //nome do executável (com extensão .exe), contido na pasta
     char descricao[MAXDESCRICAOJOGO]; //breve descrição, para fins de consulta
     int record;          //máxima pontuação já obtida nesse jogo
     int ultimo_reg_res;   //ponteiro para último registro deste jogo em resultados.dat, inicializado com -1, análogo ao do jogador
} typedef JOGO;

struct tipo_resultado
{
    int idresultado;                  // inseri para referencia de resultado
    int id;                        //referencia ao id do jogador
    int cod;                           //referencia ao código do jogo
    int pontos;                        // pontuação obtida na jogada (entre 0 e 100)
    int pos_anterior_jogador;          //ponteiro para o registro referente à jogada anterior deste
                                       // jogador (-1 indica inexistência de registro anterior)
    int pos_anterior_jogo;    //ponteiro para o registro referente à jogada anterior deste jogo
} typedef RESULTADO;

