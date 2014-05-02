//Prototipos de Funcoes
void CadastraJogador(); //ok
void ConsultaJogador(); //ok
void AlteraJogador(); //ok
void CadastraJogo(); //ok
void ConsultaJogo(); //ok
void Login(int *plogado); //ok
void Jogar(int *plogado); //ok
void AtualizaDados(int Jogo, int Jogador, int Resultado);  //ok                 
int MenuPrincipal(int *plogado); //ok
void MenuJogadores(); //ok
void MenuJogos(); //ok
void MenuRanking(); //ok
void ConsultaRanking(FILE *rank, char nome_arq[50]); //ok
void Outtxt2Vetint(int Jogo, int Jogador, char nome_arquivo[100]); //ok
void ConsultaResultados(); //ok
void AtualizaRanking(char nome_jogador[MAXNOMEJOGADOR], char nome_jogo[MAXNOMEJOGO], int resultado);
void ConsultaResultadosPorJogador(); //ok


// Funcoes para jogadores
void ConsultaJogador()
{
	JOGADOR jogador;
	int procurado=3, encontrado = 0;
	char busca[100];
	
    system ("cls");
	do
	{
	 printf ("1 Busca por id\n2 Busca por nome\n3 Mostra todos\n ");
	 fflush(stdin);
	 scanf ("%d", &procurado);
    } while (procurado != 1 && procurado != 2 && procurado != 3);
    
    if ((arq_jogadores = fopen("jogadores.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogadores.");
    }
    else
    {   
	 if(procurado != 3)
	 {
     printf ("Digite o valor a buscar: ");
	 fflush(stdin);
     scanf ("%s", busca);
     }
     do
 	 {
        if (procurado == 1) // busca por id
  	    {
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
             if (jogador.id == atoi(busca))
			 {
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s", jogador.nome);
				//printf ("Senha: %s", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Ultimo jogo: %d\n",jogador.ultimo_reg_res);
				printf ("Jogador Ativo: %c\n", jogador.ativo);
                encontrado = 1;
			 }
           }
    	}
    	else if (procurado == 2) // busca por nome
  	    {
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
             if (!(strcmp(jogador.nome,busca)))
			 {
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				//printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Ultimo jogo: %d\n",jogador.ultimo_reg_res);
                printf ("Jogador Ativo: %c\n", jogador.ativo);
                encontrado = 1;
			 }
           }
    	}
    	else if (procurado == 3) // mostra todos
  	    {
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				//printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Ultimo jogo: %d\n",jogador.ultimo_reg_res);
				printf ("Jogador Ativo: %c\n", jogador.ativo);
                printf ("-------------------------");
                encontrado = 1;
           }
    	}
    	
	 } while (!feof(arq_jogadores));
	 if (!encontrado)
		printf ("Jogador nao encontrado.\n");
     fclose(arq_jogadores);
    }  
    system("pause>NULL");
}

void CadastraJogador()
{
    int i, nomeok=0, senhaok=0, cont, asterisco, IndiceSenha=0;
    char op, tecla;
    JOGADOR NovoJogador, BuscaJogador; 
    system("cls");
    
    do // grande laco
    {
        
	// Id
	NovoJogador.id = 0;
	if ((arq_jogadores = fopen("jogadores.dat","rb")) == NULL)
	    printf ("Falha ao abrir arquivo.\n");
    else
    {
	while (!feof(arq_jogadores))
 	{
		fread(&NovoJogador,sizeof(JOGADOR),1,arq_jogadores);
		
	}
	fclose(arq_jogadores);
	NovoJogador.id = NovoJogador.id + 1;
	printf ("Novo jogador tera id: %d\n", NovoJogador.id);
    }	
	// Nome
    do
    {
    printf ("Digite um nome para o jogador: ");
    fflush(stdin);
    fgets(NovoJogador.nome,sizeof(NovoJogador.nome),stdin);
    for (cont = 0; cont < strlen(NovoJogador.nome); cont++) // troca \n por \0
        if (NovoJogador.nome[cont] == '\n')
            NovoJogador.nome[cont] = '\0';
    
    if (strlen(NovoJogador.nome) > MAXNOMEJOGADOR)
        printf("Nome muito comprido.\n");
    else if (strlen(NovoJogador.nome) == 0)
        printf("Nome nao foi digitado.\n");
    else
    {    
        if ((arq_jogadores = fopen("jogadores.dat","rb")) == NULL)
	        printf ("Falha ao abrir arquivo.\n");
        else
        { 
        while (!feof(arq_jogadores))
 	    {
		fread(&BuscaJogador,sizeof(JOGADOR),1,arq_jogadores);
		if (strcmp(BuscaJogador.nome,NovoJogador.nome))
         nomeok = 1;
        else
        {
         printf ("Nome já existe.");
         nomeok = 0;
         }
	    }
	    fclose(arq_jogadores);
        }
    }
    } while (nomeok == 0); //consiste nome
    
	// Senha
    do
    {
    printf ("Digite a senha para este jogador: ");
//    fflush(stdin);
//    fgets(NovoJogador.senha,sizeof(NovoJogador.senha),stdin);
//    for (cont = 0; cont < strlen(NovoJogador.senha); cont++) // troca \n por \0
//        if (NovoJogador.senha[cont] == '\n')
//            NovoJogador.senha[cont] = '\0';
    //gets(senha);
      do
      {
       tecla = getch();
       switch(tecla)
       {
                   case (char)13 : if(IndiceSenha>0)           
                                NovoJogador.senha[IndiceSenha] = '\0'; 
                            else
                                tecla = NULL;      
                            break;
                   case (char)8  : if(IndiceSenha>0)    
                            {
                                NovoJogador.senha[IndiceSenha] = NULL;
                                IndiceSenha--;
                            }
                            break;
 
                   default       : NovoJogador.senha[IndiceSenha] = tecla;
                            IndiceSenha++;
                            break;
        }
        asterisco = IndiceSenha;
        clrscr();
        printf("Digite a senha para este jogador: ");
        while(asterisco>0)         //IMPRIME O NR DE CHARS, EM ASTERISCOS
        {
            printf("*");
            asterisco--;
        }
     //} while (tecla!=(char)13 && strlen(senha)<MAXSENHAJOGADOR);
     } while (tecla!=(char)13); 
    
    if (strlen(NovoJogador.senha) > MAXSENHAJOGADOR)
        printf("Senha muita comprido.\n");
    else if (strlen(NovoJogador.senha) == 0)
        printf("Senha nao foi digitada.\n");
    else
        senhaok = 1;
    } while (senhaok == 0); //consiste senha
	
	// nunca jogou
	NovoJogador.jogadas = 0;
	NovoJogador.ultimo_reg_res = -1;
    NovoJogador.ativo = 's';
    	
    // Salvando no arquivo
	arq_jogadores = fopen("jogadores.dat","a+b");
    if (!arq_jogadores)
        printf ("Erro ao abrir arquivo.");
    else // grava no arquivo
        fwrite(&NovoJogador,sizeof(JOGADOR),1,arq_jogadores);
	fclose(arq_jogadores);
    
    do
    {
    printf ("Você deseja cadastrar outro jogador? S | N: ");
    scanf ("%c", &op);
    } while (tolower(op) != 'n' && tolower(op) != 's');
    
    } while ( tolower(op) == 's' ); // fim do grande laco
    
}

void AlteraJogador()
{
	JOGADOR jogador;
	int procurado, encontrado = 0, alterado, cont, jaalterado=0;
	char busca[100], op;
	
    system ("cls");
	do
	{
	 printf ("Vamos buscar o jogador a ser alterado:\n");
     printf ("1- Busca por id\n2- Busca por nome\n ");
	 fflush(stdin);
	 scanf ("%d", &procurado);
    } while (procurado != 1 && procurado != 2);
    
    if ((arq_jogadores = fopen("jogadores.dat","r+b")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogadores.");
    }
    else
    {   
	 printf ("Digite o valor a buscar: ");
	 fflush(stdin);
     scanf ("%s", busca);
     
     do
 	 {
        if (procurado == 1) // busca por id
  	    {
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
             if (jogador.id == atoi(busca))
			 {
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Jogador Ativo: %c\n", jogador.ativo);
                encontrado = 1;
                fseek(arq_jogadores,-sizeof(JOGADOR),SEEK_CUR); // volta uma estrutura no arquivo
                
                do
                {
	            printf ("\nEste foi o jogador encontrado. Vamos alterar:\n1- Nome\n2- Senha\n3- Status\n"); 
	            fflush(stdin);
	            scanf ("%d", &alterado);
                } while (alterado != 1 && alterado != 2 && alterado != 3);
                switch(alterado)
                {
                                case 1: printf ("-------------------------\n");
                                        printf("Digite o novo nome: ");
                                        fflush(stdin);
                                        fgets(jogador.nome,sizeof(jogador.nome),stdin);
                                        for (cont = 0; cont < strlen(jogador.nome); cont++) // troca \n por \0
                                                if (jogador.nome[cont] == '\n')
                                                              jogador.nome[cont] = '\0';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                                case 2: printf ("-------------------------\n");
                                        printf("Digite a nova senha: ");
                                        fflush(stdin);
                                        fgets(jogador.senha,sizeof(jogador.senha),stdin);
                                        for (cont = 0; cont < strlen(jogador.senha); cont++) // troca \n por \0
                                                if (jogador.senha[cont] == '\n')
                                                            jogador.senha[cont] = '\0';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                                case 3: do
                                        {
                                        printf ("-------------------------\n");
                                        printf("1- Ativado\n2- Desativado\n");
                                        scanf ("%d",&op);
                                        } while (op != 1 && op != 2);
                                        if (op == 1)
                                           jogador.ativo = 's';
                                        else
                                            jogador.ativo = 'n';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                }
                system ("cls");
                printf ("Jogador alterado:\n");
                fseek(arq_jogadores,-sizeof(JOGADOR),SEEK_CUR); // volta uma estrutura no arquivo
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Status Jogador: %c\n", jogador.ativo);
				jaalterado=1;
			 }
           }
    	}
    	else if (procurado == 2) // busca por nome
  	    {
           
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
             if (!(strcmp(jogador.nome,busca)))
			 {
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Status Jogador: %c\n", jogador.ativo);
                encontrado = 1;
                fseek(arq_jogadores,-sizeof(JOGADOR),SEEK_CUR); // volta uma estrutura no arquivo
                
                do
                {
	            printf ("\nEste foi o jogador encontrado. Vamos alterar:\n1- Nome\n2- Senha\n3- Status\n"); 
	            fflush(stdin);
	            scanf ("%d", &alterado);
                } while (alterado != 1 && alterado != 2 && alterado != 3);
                switch(alterado)
                {
                                case 1: printf ("-------------------------\n");
                                        printf("Digite o novo nome: ");
                                        fflush(stdin);
                                        fgets(jogador.nome,sizeof(jogador.nome),stdin);
                                        for (cont = 0; cont < strlen(jogador.nome); cont++) // troca \n por \0
                                                if (jogador.nome[cont] == '\n')
                                                              jogador.nome[cont] = '\0';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                                case 2: printf ("-------------------------\n");
                                        printf("Digite a nova senha: ");
                                        fflush(stdin);
                                        fgets(jogador.senha,sizeof(jogador.senha),stdin);
                                        for (cont = 0; cont < strlen(jogador.senha); cont++) // troca \n por \0
                                                if (jogador.senha[cont] == '\n')
                                                            jogador.senha[cont] = '\0';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                                case 3: do
                                        {
                                        printf ("-------------------------\n");
                                        printf("1- Ativado\n2- Desativado\n");
                                        scanf ("%d",&op);
                                        } while (op != 1 && op != 2);
                                        if (op == 1)
                                           jogador.ativo = 's';
                                        else
                                            jogador.ativo = 'n';
                                        fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                                        break;
                }
                system ("cls");
                printf ("Jogador alterado:\n");
                fseek(arq_jogadores,-sizeof(JOGADOR),SEEK_CUR); // volta uma estrutura no arquivo
                printf ("\nID: %d\n", jogador.id);
                printf ("Nome: %s\n", jogador.nome);
				printf ("Senha: %s\n", jogador.senha);
				printf ("Numero Jogadas: %d\n", jogador.jogadas);
				printf ("Status Jogador: %c\n", jogador.ativo);
				jaalterado=1;
             }
           }
     
        }
	 } while ((!feof(arq_jogadores)) && (jaalterado == 0));
	 if (!encontrado)
		printf ("Jogador nao encontrado.\n");
     fclose(arq_jogadores);
    }  
    system("pause>NULL");
}


void MenuRanking()
{
int cont=0;
    char tab;
    do
    {
         system("color f2");
         gotoxy(1,1);
         textbackground(GREEN);
         textcolor(BLACK);
         textbackground(WHITE); 
        
         if(cont == 0) 
         textbackground(GREEN);
         printf("1-Exibe Ranking");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 1) 
         textbackground(GREEN);
         printf("2-Consulta todos resultados");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 2) 
         textbackground(GREEN);
         printf("4-Retorna");
         textbackground(WHITE); 
         printf("\n");
         
         do
         {
                   fflush(stdin);
                   tab = getch();
         } while(!(tab==9 || tab==10 || tab==13));
         cont++;
         if(cont == 4) 
         cont=0;
      }
      while(tab==9);          
      system("cls");
      cont=cont - 1;
      switch(cont)
      {
                 case 0: ConsultaRanking(arq_rank, "ranking.txt");
                         break;
                 case 1: ConsultaResultados();
                         break;
                 case 2: MenuPrincipal(&logado);
                         break;
      }
}


void MenuJogos()
{
int cont=0;
    char tab;
    do
    {
         system("color f2");
         gotoxy(1,1);
         textbackground(GREEN);
         textcolor(BLACK);
         textbackground(WHITE); 
        
         if(cont == 0) 
         textbackground(GREEN);
         printf("1-Inclui novo jogo");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 1) 
         textbackground(GREEN);
         printf("2-Consulta jogos cadastrados");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 2) 
         textbackground(GREEN);
         printf("4-Retorna");
         textbackground(WHITE); 
         printf("\n");
         
         do
         {
                   fflush(stdin);
                   tab = getch();
         } while(!(tab==9 || tab==10 || tab==13));
         cont++;
         if(cont == 4) 
         cont=0;
      }
      while(tab==9);          
      system("cls");
      cont=cont - 1;
      switch(cont)
      {
                 case 0: CadastraJogo();
                         break;
                 case 1: ConsultaJogo();
                         break;
                 case 2: MenuPrincipal(&logado);
                         break;
      }
}


void MenuJogadores()
{
    int cont=0;
    char tab;
    do
    {
         system("color f2");
         gotoxy(1,1);
         textbackground(GREEN);
         textcolor(BLACK);
         textbackground(WHITE); 
        
         if(cont == 0) 
         textbackground(GREEN);
         printf("1-Inclui novo jogador");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 1) 
         textbackground(GREEN);
         printf("2-Consulta jogadores cadastrados");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 2) 
         textbackground(GREEN);
         printf("3-Consulta resultados do jogador");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 3) 
         textbackground(GREEN);
         printf("4-Altera jogador");
         textbackground(WHITE); 
         printf("\n"); 
         
         if(cont == 4) 
         textbackground(GREEN);
         printf("5-Retorna");
         textbackground(WHITE); 
         printf("\n"); 
      


         
         do
         {
                   fflush(stdin);
                   tab = getch();
         }
         while(!(tab==9 || tab==10 || tab==13));
         cont++;
         if(cont == 6) 
         cont=0;
      
      }
      while(tab==9);          
      system("cls");
      cont=cont - 1;
      switch(cont)
      {
                 case 0: CadastraJogador();
                         break;
                 
                 case 1: ConsultaJogador();
                         break;
                 case 2: ConsultaResultadosPorJogador();
                         break;
                 case 3: AlteraJogador();
                         break;
                 case 4: MenuPrincipal(&logado);
                         break;
      }
}

int MenuPrincipal(int *plogado)
{ 

    int cont=0, opcao,retorno=0;
    char tab;
    char nome[30];
    system("cls");

    if (*plogado != 0)
       opcao = 6;
    else
       opcao = 5;
    
    do
    {
         system("color f2");
         gotoxy(1,1);
         textbackground(GREEN);
         textcolor(BLACK);
         textbackground(WHITE); 
        
         if(cont == 0) 
         textbackground(GREEN);
         if (*plogado != 0) //caso esteja logado
            printf("1-Fazer Logout");
         else
             printf("1-Fazer Login");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 1) 
         textbackground(GREEN);
         printf("2-Incluir/consultar/remover jogadores");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 2) 
         textbackground(GREEN);
         printf("3-Incluir/consultar jogos");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 3) 
         textbackground(GREEN);
         printf("4-Ranking");
         textbackground(WHITE); 
         printf("\n");
         
          if(cont == 4) 
         textbackground(GREEN);
         printf("5-Sair");
         textbackground(WHITE); 
         printf("\n");
         
         if(cont == 5) 
         textbackground(GREEN);
         if (*plogado != 0) //caso esteja logado
            textcolor(BLACK);
         else
            textcolor(LIGHTGRAY); 
         printf("6-Jogar");
         textcolor(BLACK);
         textbackground(WHITE); 
         printf("\n"); 
         
              
         
         do
         {
                   fflush(stdin);
                   tab = getch();
         } while(!(tab==9 || tab==10 || tab==13));
         if (tab == 9)
         {
          cont++;
          if(cont == opcao) 
                 cont=0;
         }
      } while(tab==9);          
      system("cls");
      //cont--;
      
      switch(cont)
      {
                 case 0: if(*plogado == 0)      //se logado=1, ja esta logado
                              {
                              Login(&logado);
                              }
                         else
                              {
                              *plogado=0;
                              MenuPrincipal(&logado);
                              }
                         break;
                 
                 case 1: MenuJogadores();
                         break;
                 
                 case 2: MenuJogos();
                         break;
                 
                 case 3: MenuRanking();
                         break;
                         
                 case 4: retorno=1; // para encerrar programa
                         break;
                         
                 case 5: Jogar(&logado);
                         break;
      }

      return retorno;
}



void ConsultaRanking(FILE *rank, char nome_arq[50])
{
     char carac;
     int i=0;
     if((rank = fopen(nome_arq, "r"))==NULL)
             printf("erro de abertura do arquivo ranking.txt\n");
     else
     {
         carac=getc(rank);
         while(!(feof(rank)))
          {
                if (carac == '#')
                {
                printf("\nJogo: ");
                carac=getc(rank);
                do
                {
                  printf("%c", carac);
                  carac=getc(rank);
                }while((carac != '@') && (carac != '\n') && (!(feof(rank)))); 
                }
                else if (carac == '@')
                {
                printf("\n\tPontuacao: ");
                carac=getc(rank);
                do
                {
                  printf("%c", carac); 
                   carac=getc(rank);
                }while((carac != '&') && (carac != '\n')&& (!(feof(rank))));
                }
                else if(carac == '&')
                {
                printf("\n\t\tJogador(es): ");
                carac=getc(rank);
                do
                {
                if (carac != '&')
                  printf("%c", carac); 
                carac=getc(rank);
                }while((carac != '@') && (carac != '\n')&& (!(feof(rank))));
                }
                else
                  carac=getc(rank);
         }
       fclose(rank);
     }  
system("pause>NULL");
}


//Funções para jogos
void CadastraJogo()
{
    int i, nomeok=0, pastaok=0, descricaook=0, execok=0, cont;
    char op;
    JOGO NovoJogo, BuscaJogo; 
    system("cls");
    
    do // grande laco
    {
        
	// Cod
	NovoJogo.cod = 0;
	if ((arq_jogos = fopen("jogos.dat","rb")) == NULL)
	    printf ("Falha ao abrir arquivo.\n");
    else
    {
	while (!feof(arq_jogos))
 	{
		fread(&NovoJogo,sizeof(JOGO),1,arq_jogos);
		
	}
	fclose(arq_jogos);
	NovoJogo.cod = NovoJogo.cod + 1;
	printf ("Novo jogo tera cod: %d\n", NovoJogo.cod);
    }	
	// Nome
    do
    {
    printf ("Digite um nome para o jogo: ");
    fflush(stdin);
    fgets(NovoJogo.jogo,sizeof(NovoJogo.jogo),stdin);
    for (cont = 0; cont < strlen(NovoJogo.jogo); cont++) // troca \n por \0
        if (NovoJogo.jogo[cont] == '\n')
            NovoJogo.jogo[cont] = '\0';
    
    if (strlen(NovoJogo.jogo) > MAXNOMEJOGO)
        printf("Nome muito comprido.\n");
    else if (strlen(NovoJogo.jogo) == 0)
        printf("Nome nao foi digitado.\n");
    else
    {    
        if ((arq_jogos = fopen("jogos.dat","rb")) == NULL)
	        printf ("Falha ao abrir arquivo.\n");
        else
        { 
        while (!feof(arq_jogos))
 	    {
		 fread(&BuscaJogo,sizeof(JOGO),1,arq_jogos);
		 if (strcmp(BuscaJogo.jogo,NovoJogo.jogo))
          nomeok = 1;
         else
         {
          printf ("Nome já existe.");
          nomeok = 0;
         }
	    }
	    fclose(arq_jogos);
        }
    }
    } while (nomeok == 0); //consiste nome
    
	// Pasta
    do
    {
    printf ("Digite a pasta deste jogo: ");
    fflush(stdin);
    fgets(NovoJogo.pasta,sizeof(NovoJogo.pasta),stdin);
    for (cont = 0; cont < strlen(NovoJogo.pasta); cont++) // troca \n por \0
        if (NovoJogo.pasta[cont] == '\n')
            NovoJogo.pasta[cont] = '\0';
    
    if (strlen(NovoJogo.pasta) > MAXPASTAJOGO)
        printf("Path da pasta muito comprido.\n");
    else if (strlen(NovoJogo.pasta) == 0)
        printf("Path da pasta nao foi digitado.\n");
    else
        pastaok = 1;
    } while (pastaok == 0); //consiste pasta
	
	// Executavel
    do
    {
    printf ("Digite o nome do executavel deste jogo: ");
    fflush(stdin);
    fgets(NovoJogo.exec,sizeof(NovoJogo.exec),stdin);
    for (cont = 0; cont < strlen(NovoJogo.exec); cont++) // troca \n por \0
        if (NovoJogo.exec[cont] == '\n')
            NovoJogo.exec[cont] = '\0';
    
    if (strlen(NovoJogo.exec) > MAXEXECJOGO)
        printf("Nome do executavel muito comprido.\n");
    else if (strlen(NovoJogo.exec) == 0)
        printf("Nome do executavel foi digitado.\n");
    else
        execok = 1;
    } while (execok == 0); //consiste exec
	
	// Descricao
    do
    {
    printf ("Digite a descricao para este jogo: ");
    fflush(stdin);
    fgets(NovoJogo.descricao,sizeof(NovoJogo.descricao),stdin);
    for (cont = 0; cont < strlen(NovoJogo.descricao); cont++) // troca \n por \0
        if (NovoJogo.descricao[cont] == '\n')
            NovoJogo.descricao[cont] = '\0';
    
    if (strlen(NovoJogo.descricao) > MAXDESCRICAOJOGO)
        printf("Descricao muito comprida.\n");
    else if (strlen(NovoJogo.descricao) == 0)
        printf("Descricao nao foi digitada.\n");
    else
        descricaook = 1;
    } while (descricaook == 0); //consiste senha
	
	// nunca foi jogado
	NovoJogo.record = 0;
	NovoJogo.ultimo_reg_res = -1;
        	
    // Salvando no arquivo
	arq_jogos = fopen("jogos.dat","a+b");
    if (!arq_jogos)
        printf ("Erro ao abrir arquivo.");
    else // grava no arquivo
        fwrite(&NovoJogo,sizeof(JOGO),1,arq_jogos);
	fclose(arq_jogos);
    
    do
    {
    printf ("Você deseja cadastrar outro jogo? S | N: ");
    scanf ("%c", &op);
    } while (tolower(op) != 'n' && tolower(op) != 's');
    
    } while ( tolower(op) == 's' ); // fim do grande laco
    
}

void ConsultaJogo()
{
	JOGO jogo;
	int procurado, encontrado = 0;
	char busca[100];
	
    system ("cls");
	do
	{
	 printf ("1 Busca por cod\n2 Busca por nome\n3 Mostra todos\n ");
	 fflush(stdin);
	 scanf ("%d", &procurado);
    } while (procurado != 1 && procurado != 2 && procurado != 3);
    
    if ((arq_jogos = fopen("jogos.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogos.");
    }
    else
    {   
	 if(procurado != 3)
	 {
     printf ("Digite o valor a buscar: ");
	 fflush(stdin);
     scanf ("%s", busca);
     }
     do
 	 {
        if (procurado == 1) // busca por id
  	    {
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
             if (jogo.cod == atoi(busca))
			 {
                printf ("\nID: %d\n", jogo.cod);
                printf ("Nome: %s", jogo.jogo);
				printf ("Pasta: %s\n", jogo.pasta);
				printf ("Executavel: %s\n", jogo.exec);
				printf ("Uma breve descricao: %s\n", jogo.descricao);
                printf ("Record: %d\n", jogo.record);
                printf ("Ultima vez jogado: %d\n", jogo.ultimo_reg_res);
                encontrado = 1;
			 }
           }
    	}
    	else if (procurado == 2) // busca por nome
  	    {
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
             if (!(strcmp(jogo.jogo,busca)))
			 {
                printf ("\nID: %d\n", jogo.cod);
                printf ("Nome: %s\n", jogo.jogo);
				printf ("Pasta: %s\n", jogo.pasta);
				printf ("Executavel: %s\n", jogo.exec);
				printf ("Uma breve descricao: %s\n", jogo.descricao);
				printf ("Record: %d\n", jogo.record);
                printf ("Ultima vez jogado: %d\n", jogo.ultimo_reg_res);
                encontrado = 1;
			 }
           }
    	}
    	else if (procurado == 3) // mostra todos
  	    {
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
                printf ("\nID: %d\n", jogo.cod);
                printf ("Nome: %s\n", jogo.jogo);
				printf ("Pasta: %s\n", jogo.pasta);
				printf ("Executavel: %s\n", jogo.exec);
				printf ("Uma breve descricao: %s\n", jogo.descricao);
				printf ("Record: %d\n", jogo.record);
                printf ("Ultima vez jogado: %d\n", jogo.ultimo_reg_res);
                printf ("-------------------------");
                encontrado = 1;
           }
    	}

	 } while (!feof(arq_jogos));
	 if (!encontrado)
		printf ("Jogo nao encontrado.\n");
     fclose(arq_jogos);
    }  
    system("pause>NULL");    
}

void Login(int *plogado)
{
     int usuariook=0, senhaok=0, IndiceSenha=0, asterisco;
     char usuario[100], senha[100], tecla;
     JOGADOR BuscaJogador;
     
     system ("cls");
     //Entrada de Dados
     do
     {
     printf ("Usuario: ");
     gets(usuario);
     } while (strlen(usuario)>MAXNOMEJOGADOR);
      system ("cls");
      printf ("Senha: ");
     //gets(senha);
      do
      {
       tecla = getch();
       switch(tecla)
       {
                   case (char)13 : if(IndiceSenha>0)           
                                senha[IndiceSenha] = '\0'; 
                            else
                                tecla = NULL;      
                            break;
                   case (char)8  : if(IndiceSenha>0)    
                            {
                                senha[IndiceSenha] = NULL;
                                IndiceSenha--;
                            }
                            break;
 
                   default       : senha[IndiceSenha] = tecla;
                            IndiceSenha++;
                            break;
        }
        asterisco = IndiceSenha;
        clrscr();
        printf("Senha : ");
        while(asterisco>0)         //IMPRIME O NR DE CHARS, EM ASTERISCOS
        {
            printf("*");
            asterisco--;
        }
     //} while (tecla!=(char)13 && strlen(senha)<MAXSENHAJOGADOR);
     } while (tecla!=(char)13);
     // Confere Dados
     if ((arq_jogadores = fopen("jogadores.dat","rb")) == NULL)
    {
        printf ("Erro ao abrir o arquivo de jogadores.");
    }
    else
    {
        while (!feof(arq_jogadores))
 	    {
		 fread(&BuscaJogador,sizeof(JOGADOR),1,arq_jogadores);
		 if (!(strcmp(BuscaJogador.nome,usuario)))
          usuariook = 1;
         if (!(strcmp(BuscaJogador.senha,senha)))
          senhaok = 1;
	    }
	    if (usuariook == 1)
	       if (senhaok == 1)
	          {
              *plogado = BuscaJogador.id;
              printf ("\nLogin ok. -> logado = %d", *plogado);
              }
           else
               printf ("\nSenha errada.");
        else
            printf ("\nUsuario nao encontrado.");
        system("pause>NULL");
    }        

}

void Jogar(int *plogado)
{
     JOGO jogo;
     int i,j, encontrado=0, opcaojogo=0, resultados[255];
     char path[255];

    if ((arq_jogos = fopen("jogos.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogos.");
    }
    else
    {   
     printf("Digite:\n");
	 do
 	 {
    
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
                printf ("%d para jogar %s\n", jogo.cod, jogo.jogo);
                encontrado = 1;
           }
    
	 } while (!feof(arq_jogos));
     scanf("%d",&opcaojogo);
	 if (!encontrado)
		{
           printf ("Nao ha jogos cadastrados.\n");
		   system("pause>NULL");
        }
     else //tem ao menos 1 jogo
     {
      encontrado = 0;
      rewind(arq_jogos);
      do
 	  {
    
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
                if (jogo.cod == opcaojogo)
                   {
                    //system(printf("%s%s\n",jogo.pasta,jogo.exec));
                    //system(path);
                    
                    encontrado = 1;
                    //Abre jogo
                    if (opcaojogo == 1)
                       system("c:\\PainelControleJogos\\jogos\\forca\\winforca.exe");
                    else if (opcaojogo == 2)
                       system("c:\\PainelControleJogos\\jogos\\musical\\musical.exe");  
                    
                    //Vamos ler o out.txt e armazenar os resultados em um vetor de inteiros
                    Outtxt2Vetint(jogo.cod, *plogado, "out.txt");
                    //resultados = Outtxt2Vetint("out.txt");
                    //for (i=0; i< sizeof(resultados); i++)
                      //  AtualizaDados(jogo.cod, 1, resultados[i]);                    
                        //AtualizaDados(jogo.cod, *plogado, resultados[i]);                    
                    //tentativa de fazer melhor, sem sucesso :p
                    /*for (i=0;(i<strlen(jogo.pasta)) && (jogo.pasta[i] != '\0');i++)
                        path[i]=jogo.pasta[i];
                    i++;
                    printf("1. %s\n",path);
                    
                    for (j=0;(j<strlen(jogo.exec)) && (jogo.exec[j] != '\0');j++)
                        {
                        path[i]=jogo.exec[j];
                        i++;
                        }
                    printf("2. %s\n",path);

                    //system(path);*/

                   
                   }
           }
      } while ((!feof(arq_jogos)) && encontrado == 0);      
     if (!encontrado)
		{
           printf ("Digite um numero valido.\n");
		   system("pause>NULL");
        }
     
     }
     fclose(arq_jogos);
    }  
		   system("pause>NULL");    
}

//Le um arquivo txt com numeros separados por * e retorna um vetor de inteiros
void Outtxt2Vetint(int Jogo, int Jogador, char nome_arquivo[100])
{
    int i=0, NumeroEmInt[19], j=0;
    char carac, NumeroEmCaracter[]={'0', '0', '0'};
    if((arq_out = fopen(nome_arquivo, "r")) == NULL)
            printf("erro de abertura");
    else
    {  
       while((carac=getc(arq_out)) != EOF)
       {
           
           do
           {
              NumeroEmCaracter[0] = NumeroEmCaracter[1];
              NumeroEmCaracter[1] = NumeroEmCaracter[2];
              NumeroEmCaracter[2]=carac;//começa a ler pelas unidades
              i++;
              carac=getc(arq_out);
           } while(carac != '*');
           
           NumeroEmInt[j] = atoi(NumeroEmCaracter);
           //printf("aqui: %d\n",NumeroEmInt[j]);
           AtualizaDados(Jogo, Jogador, NumeroEmInt[j]);
           NumeroEmCaracter[0]='0';
           NumeroEmCaracter[1]='0';
           NumeroEmCaracter[2]='0';
           i = 0;
           j++;
       }
       fclose(arq_out);
     }
   
}

void AtualizaDados(int Jogo, int Jogador, int Resultado)
{
     RESULTADO NovoResultado, resultado;
     JOGADOR  jogador;
     JOGO jogo;
     int jogador_encontrado=0, jogo_encontrado=0, jaalterado=0;
     
     // Id do novo resultado
	NovoResultado.idresultado = 0;
	if ((arq_resul = fopen("resultados.dat","rb")) == NULL)
	    printf ("Falha ao abrir arquivo de resultados.\n");
    else
    {
	while (!feof(arq_resul))
 	{
		fread(&NovoResultado,sizeof(RESULTADO),1,arq_resul);
	}
	fclose(arq_resul);
	NovoResultado.idresultado = NovoResultado.idresultado + 1;
     
     //atualiza resultados.dat
     if ((arq_resul = fopen("resultados.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de resultados.");
    }
    else
    {   
	 do
 	 {
           fread(&resultado,sizeof(RESULTADO),1,arq_resul);
		   if (!feof(arq_resul)) // para nao repetir 2 vezes
		   {
                if (resultado.id == Jogador)
                   {
                   NovoResultado.pos_anterior_jogador = resultado.idresultado;
                   jogador_encontrado = 1;
                   }
                if (resultado.cod == Jogo)
                   {
                   NovoResultado.pos_anterior_jogo = resultado.idresultado;   
                   jogo_encontrado = 1;
                   }
           }
    } while (!feof(arq_resul));
    fclose(arq_resul);
        
    if (jogador_encontrado == 0)
       NovoResultado.pos_anterior_jogador = -1;
    if (jogo_encontrado == 0)
       NovoResultado.pos_anterior_jogo = -1;   
    
    //Parametros passados na chamada da subrotina
    NovoResultado.pontos = Resultado;
    NovoResultado.id = Jogador;
    NovoResultado.cod = Jogo;
  
    //Grava no arquivo
     if ((arq_resul = fopen("resultados.dat","a+b")) == NULL)
     {
      printf ("Erro ao abrir o arquivo de resultados.");
     }
     else
     {
       fwrite(&NovoResultado,sizeof(RESULTADO),1,arq_resul);
       fclose(arq_resul);
     }
    }

    
     //atualiza jogadores.dat
    if ((arq_jogadores = fopen("jogadores.dat","r+b")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogadores.");
    }
    else
    {   
	 do
 	 {
           fread(&jogador,sizeof(JOGADOR),1,arq_jogadores);
		   if (!feof(arq_jogadores)) // para nao repetir 2 vezes
		   {
             if (jogador.id == Jogador)
			 {
                jogador.ultimo_reg_res = NovoResultado.idresultado;
                jogador.jogadas++;
                fseek(arq_jogadores,-sizeof(JOGADOR),SEEK_CUR); // volta uma estrutura no arquivo
                fwrite(&jogador,sizeof(JOGADOR),1,arq_jogadores);
                jaalterado=1;
             }
           }     
     } while (!feof(arq_jogadores) && (jaalterado == 0));
     fclose(arq_jogadores);
    }
    
    //atualiza jogos.dat
    jaalterado=0;
    if ((arq_jogos = fopen("jogos.dat","r+b")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de jogos.");
    }
    else
    {   
	 do
 	 {
           fread(&jogo,sizeof(JOGO),1,arq_jogos);
		   if (!feof(arq_jogos)) // para nao repetir 2 vezes
		   {
             if (jogo.cod == Jogo)
			 {
                jogo.ultimo_reg_res = NovoResultado.idresultado;
                if (jogo.record < NovoResultado.pontos)
                   jogo.record = NovoResultado.pontos;
                fseek(arq_jogos,-sizeof(JOGO),SEEK_CUR); // volta uma estrutura no arquivo
                fwrite(&jogo,sizeof(JOGO),1,arq_jogos);
                jaalterado=1;
             }
           }     
     } while (!feof(arq_jogos) && (jaalterado == 0));
     fclose(arq_jogos);
    }


    //atualiza ranking.txt
    AtualizaRanking(jogador.nome, jogo.jogo, NovoResultado.pontos);    

    
  } //fim do primeiro else
}


void ConsultaResultados()
{
    RESULTADO resultado;
 
 
     if ((arq_resul = fopen("resultados.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de resultados.");
    }
    else
    {   
	do
 	 {
         fread(&resultado,sizeof(RESULTADO),1,arq_resul);
       if (!feof(arq_resul)) // para nao repetir 2 vezes
		   {
           printf ("ID Resultado: %d\n",resultado.idresultado);
           printf ("ID Jogador: %d\n",resultado.id);
           printf ("COD Jogo: %d\n",resultado.cod);
           printf ("Pontos: %d\n",resultado.pontos);
           printf ("Resultado Anterior Jogador: %d\n",resultado.pos_anterior_jogador);
           printf ("Resultado Anterior Jogo: %d\n",resultado.pos_anterior_jogo);
           printf ("----------------------------------\n");
           }
     }  while (!feof(arq_resul));
     
}
system("pause>NULL");
}


void ConsultaResultadosPorJogador()
{
    RESULTADO resultado;
    int busca;
    
     if ((arq_resul = fopen("resultados.dat","rb")) == NULL)
    {
     printf ("Erro ao abrir o arquivo de resultados.");
    }
    else
    {   
	   printf ("Digite o id do Jogador: ");
	   fflush(stdin);
       scanf ("%d", &busca);
    
      do
 	  {
         fread(&resultado,sizeof(RESULTADO),1,arq_resul);
       if (!feof(arq_resul)) // para nao repetir 2 vezes
		   {
             if ((resultado.id == busca))
			 {
               printf ("ID Resultado: %d\n",resultado.idresultado);
               printf ("COD Jogo: %d\n",resultado.cod);
               printf ("Pontos: %d\n",resultado.pontos);
               printf ("----------------------------------\n");
             }
           }
      }  while (!feof(arq_resul));
     
}
system("pause>NULL");
}



void AtualizaRanking(char nome_jogador[MAXNOMEJOGADOR], char nome_jogo[MAXNOMEJOGO], int resultado)
{
     char linha[255], novalinha[255],jogo_arquivo[MAXNOMEJOGO], ponto_arquivo[3], resultado_char[3];
     int i=0, j=0,x=0;
     
      if((arq_rank = fopen("ranking.txt", "r"))==NULL)
             printf("erro de abertura do arquivo ranking.txt\n");
     else
     {
         
         do
         {
         fgets(linha,255,arq_rank);
         for (i=0;(linha[i] != '#');i++); //posiciona no nome do jogo
         i++; //posiciona no inicio do nome do jogo
         while ((linha[i] != ' ') && (linha[i] != '\n') && (linha[i] != '@'))
         {
               jogo_arquivo[j] = linha[i];
               j++;
               i++;
         } 
         jogo_arquivo[j] = '\0';
         } while ((strcmp(jogo_arquivo,nome_jogo)) && (!(feof(arq_rank))));

         //verifica pontuacoes
         do
         {
         ponto_arquivo[0]= '0';
         ponto_arquivo[1]= '0';
         ponto_arquivo[2]= '0';
         for (;(linha[i] != '@');i++); //posiciona nas pontuacoes
         i++; //posiciona no inicio da pontuacao
         while ((linha[i] != ' ') && (linha[i] != '\n') && (linha[i] != '&'))
         {
               ponto_arquivo[0] = ponto_arquivo[1];
               ponto_arquivo[1] = ponto_arquivo[2];
               ponto_arquivo[2] = linha[i];
               i++;
         } 
         ponto_arquivo[j] = '\0';
         //puts(ponto_arquivo);
         
         } while (resultado < atoi(ponto_arquivo));
         
         //verifica se eh igual ou maior
         if (resultado == atoi(ponto_arquivo))
         {
             for (j=0;j<i;j++) //copia parte inicial do ranking
                 novalinha[j] = linha[j];
             novalinha[j]= ' '; // para eliminar o finalizador de string
             j++;
             novalinha[j]='&';
             j++;
             for (x=0;x<strlen(nome_jogador);x++) //insere nome do jogador
                 {
                 novalinha[j] = nome_jogador[x];
                 j++;
                 }
             novalinha[j]= ' '; // para eliminar o finalizador de string
             j++;
             for (;i<strlen(linha);i++)   //insere restante da linha
                 {
                 novalinha[j]=linha[i];
                 j++;
                 //printf ("%d - %d: %c - %c\n",i,j,novalinha[j],linha[i]);
                 //system("pause>NULL");
                 }
             novalinha[j]='\n';
             j++;
             novalinha[j]='\0';
             //puts(novalinha);
         }
         else //se nao eh igual com certeza eh maior
         {
              while (linha[i] != '@') //reposiciona o i para acrescentar novo resultado
                    i--;
             i--; //para ficar ateh 1 antes do @ 
              
              for (j=0;j<i;j++) //copia parte inicial do ranking
                    novalinha[j] = linha[j];
             novalinha[j]= ' '; // para eliminar o finalizador de string
             j++;
             novalinha[j]= '@';
             j++;
             itoa(resultado,resultado_char,10);
             for (x=0;x<strlen(resultado_char);x++) //insere resultado
                 {
                 novalinha[j] = resultado_char[x];
                 j++;
                 }
             novalinha[j] = '&';
             for (x=0;x<strlen(nome_jogador);x++) //insere nome do jogador
                 {
                 novalinha[j] = nome_jogador[x];
                 j++;
                 }
             for (;i<strlen(linha);i++)   //insere restante da linha
                 {
                 novalinha[j]=linha[i];
                 j++;
                 //printf ("%d - %d: %c - %c\n",i,j,novalinha[j],linha[i]);
                 //system("pause>NULL");
                 }
             novalinha[j]='\n';
             j++;
             novalinha[j]='\0';                 
             //puts(novalinha);
         }
         fclose(arq_rank);         
     
         //agora agente vai atualiza a tosquera
         if((arq_rank = fopen("ranking.txt", "r+"))==NULL)
             printf("erro de abertura do arquivo ranking.txt\n");
         else
         {
         
           do
           {
           fgets(linha,255,arq_rank);
           //puts(linha);
           for (i=0;(linha[i] != '#');i++); //posiciona no nome do jogo
           i++; //posiciona no inicio do nome do jogo
           j=0;
           while ((linha[i] != ' ') && (linha[i] != '\n') && (linha[i] != '@'))
           {
               jogo_arquivo[j] = linha[i];
               j++;
               i++;
           } 
           jogo_arquivo[j] = '\0';
           //printf("%s - %s\n",jogo_arquivo,nome_jogo);
           if (!(strcmp(jogo_arquivo,nome_jogo))) // se for a linha que atualizamos
              {
              //fputs(novalinha,arq_rank);
              puts(novalinha);
              }
           else
               {
               //fputs(linha,arq_rank);
               puts(linha);
               }
           
           
           } while (!(feof(arq_rank)));
         }
     }    
}
