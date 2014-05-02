; Jogo da Vida para Intel x86
; 3º Trabalho - Arquitetura de Computadores I
; Professora: Taisy Weber
; Aluno: Germano de Mello Andersson, matr. 137719
; 2008/02




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Inicio Segmento de Pilha ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PILHA   SEGMENT STACK
	DW 128 DUP (?)
PILHA   ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Fim Segmento de Pilha ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Inicio Segmento de Dados ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
DADOS   SEGMENT

	;constantes
	MAXLINHA	EQU	25
	MAXCOLUNA	EQU	60
	CR		EQU	0DH ; carriage return
	LF		EQU	0AH ; line feed
	leitura		equ	0
	escrita		equ	1


	;variaveis
	GERACAO		DW	0
	msgerro		db	'tente outra vez','$'
	ppw		db	'Passo a passo','$'
	branco		db	'               ','$'
	nome		dB	12 dup(?),'$'
	geracaotxt	db	'0000000000','$'
	continuow	db	'Continuo','$'
	lixobom		db	'000000'
	convertido	db	'0000','$'	 ; memoria com resultado da conversao binario to asc
	MATRIZORIG	DB	1674 DUP (0)
	MATRIZTEMP	DB	1674 DUP (0)
	
	pauseado	db	'pause!','$'
	CONTADOR DW ?
	LINHA		DB	1
	COLUNA		DB	1
	VIZINHOS	DB	0
	indiceorig	DW	?
	tempo		db	2	dup(?),'$'
	indicetemp	DW	?
	ESTADOATUAL	DB	?
	num		db	0
	QUALQUERCOISA	DB	?
	
	arqtelainicial  db	'tela1.txt',0H
	
	
	tempoint	dw	0
	
	buffer		dB	128 dup(?),'$'
	handler		dw	?
	matrizok	db	0
	temporizador	dw	0
	telainiciala	db	'| Arquivo:         ','$'
	telainicialb	db	'|                  ','$'
	telainicialc	db	'|                  ','$'
	telainiciald	db	'| Geracoes:        ','$'
	telainiciale	db	'| 0000000000       ','$'
	telainicialf	db	'|                  ','$'
	telainicialg	db	'| Modo:            ','$'
	telainicialh	db	'|                  ','$'
	telainiciali	db	'|                  ','$'
	telainicialj	db	'| Temporizador:    ','$'
	telainicialk	db	'|  0               ','$'
	telainiciall	db	'|                  ','$'
	telainicialm	db	'+------------------','$'
	telainicialn	db	'| Comandos:        ','$'
	telainicialo	db	'| P: passo a passo ','$'
	telainicialp	db	'| R: rodar         ','$'
	telainicialq	db	'| T: def. tempo    ','$'
	telainicialr	db	'| C: carga arquivo ','$'
	telainicials	db	'| Q: terminar      ','$'
	telainicialt	db	'+------------------','$'
	telainicialu	db	'| Entrada:         ','$'
	telainicialv	db	'|                  ','$'
	telainicialw	db	'| Mensagens:       ','$'
	telainicialx	db	'|                  ','$'
	telainicialy	db	'|                  ','$'



DADOS   ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Fim Segmento de Dados ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Inicio Segmento de Codigo ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CODIGO  SEGMENT
	ASSUME CS: CODIGO, SS: PILHA, DS: DADOS, ES: DADOS
	

	;### Programa Principal ###
	START:		MOV AX, DADOS    ; Inicializa segmento de dados
			MOV DS, AX
			
			
			;prepara menus
			CALL TELAINICIAL2
			;prepara borda das matrizes na memoria
			CALL MONTAMATRIZES
			

	AguardaTecla:	
			;reposiciona cursor
			mov    dh,0		; linha zero  
		        mov    dl,0		; coluna zero
		        mov    bh,0		; numero da pagina (zero = primeira)
		        mov    ah,2            ; set cursor position
		        int    10h 

			; espera pela digitacao de uma tecla
			mov ah,8	 
			int 21h
			
			CMP AL,'C'
			JZ CargaDeArquivo
			CMP AL,'P'
			JZ PassoAPasso
			CMP AL,'T'
			JZ AlteraTimer
			CMP AL,'R'
			JZ Rodar
			CMP AL,'Q'
			JZ SairPrograma
			CMP AL,'c'
			JZ CargaDeArquivo
			CMP AL,'p'
			JZ PassoAPasso
			CMP AL,'t'
			JZ AlteraTimer
			CMP AL,'r'
			JZ Rodar
			CMP AL,'q'
			JZ SairPrograma
			JMP AguardaTecla

	CargaDeArquivo: CALL LEARQUIVO
			JMP AguardaTecla

	PassoAPasso:	CALL ESCREVEPASSOAPASSO
			CALL PASSAGERACAO
			CALL MOSTRAMATRIZORIG
			JMP AguardaTecla
	
	AlteraTimer:	CALL DEFINETEMPORIZADOR	
			JMP AguardaTecla

	Rodar:		CALL ESCREVECONTINUO
			CALL PASSAGERACAO
			CALL MOSTRAMATRIZORIG
			
			;obtendo primeiro tick
	 		MOV AH,00H
			INT 1AH
			
			;primeiro tick eh somado ao temporizador adicionado pelo user			
			MOV BX,DX			
			ADD BX,TEMPOINT
			
	lacodotempo:	;obtendo segundo tick
			MOV AH,00H
			INT 1AH
			;testa se segundo tick ja eh maior q primeiro
			CMP BX,DX
			JNS lacodotempo
			
			

			;verificando se um caracter foi digitado
			MOV AH,1
			INT 16H
			JE Rodar
			
			; espera pela digitacao de uma tecla
			mov ah,8	 
			int 21h			

			JMP AguardaTecla


	SairPrograma:	MOV AH, 4CH ; Retorna ao DOS
			INT 21H


TELAINICIAL2	PROC	NEAR

	mov bl,24
 loopg: mov dl, LF
	mov ah,2
	int 21h
	dec bl
	jnz loopg		



	mov    dh,0		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainiciala ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,1		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialb ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS
	
	mov    dh,2		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialc ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS
	
	mov    dh,3		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainiciald ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS
	
	mov    dh,4		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainiciale ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,5		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialf ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,6		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialg ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,7		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialh ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,8		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainiciali ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,9		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialj ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,10		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialk ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,11		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainiciall ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,12		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialm ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,13		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialn ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,14		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialo ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,15		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialp ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,16		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialq ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,17		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialr ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,18		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicials ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,19		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialt ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,20		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialu ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,21		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialv ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,22		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialw ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,23		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialx ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS

	mov    dh,23		; linha zero  
	mov    dl,61		; coluna zero
	mov    bh,0		; numero da pagina (zero = primeira)
	mov    ah,2            ; set cursor position
	int	10h
	lea    dx,telainicialy ; endereco da mensagem em DX
	mov    ah,9     ; funcao exibir mensagem no AH
	int    21h      ; chamada do DOS


	RET

TELAINICIAL2	ENDP




;### Sub-rotina Imprime tela inicial ###
	TELAINICIAL PROC NEAR
			; reposiciona cursor no campo entrada
			mov    dh,0		; linha zero  
			mov    dl,0		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int	10h


			; abre arquivo para leitura
			MOV AH,3DH	;funcao ler arquivo
			MOV AL,leitura	;seleciona modo de abertura do arquivo
			LEA DX,arqtelainicial ;?
			INT 21H		;systemcall
		
			MOV HANDLER,AX
	lacoTelaInicial:
			MOV AH,3FH	;funcao ler caracter arquivo
			MOV BX,HANDLER
			MOV CX,1	;numero de bytes a serem lidos
			LEA DX,BUFFER
			INT 21H
		
			CMP AX,CX
			JNE fimTelaInicial
			MOV dl, buffer ; escreve caracter na tela
			MOV ah,2
			INT 21h
         
			MOV dl, buffer ; escreve na tela até encontrar um LF (fim de linha)
			CMP dl, LF
			JNE lacoTelaInicial
			
								
			;MOV ah,8  ; espera pela digitacao de uma tecla qualquer
			;INT 21h
			JMP lacoTelaInicial
	fimTelaInicial:	
			mov ah,3eh ; fecha arquivo
			mov bx,handler
			int 21h
			ret
	TELAINICIAL ENDP







PASSAGERACAO	PROC NEAR

			; prepara variaveis
			MOV LINHA,1
			MOV COLUNA,1
			
			;posiciona ponteiro na primeira celula valida 
			LEA SI, MATRIZORIG
			LEA DI, MATRIZTEMP
			ADD SI, 63
			ADD DI, 63
			
			

	ANALISA:	;vamos verificar quantos vizinhos vivos
			MOV DL,[SI]
			MOV ESTADOATUAL,DL
			MOV VIZINHOS,0
			MOV BL,'#'
			CMP [SI-63],BL
			JNE teste2
			INC VIZINHOS
	teste2:		CMP [SI-62],BL
			JNE teste3
			INC VIZINHOS			
	teste3:		CMP [SI-61],BL
			JNE teste4
			INC VIZINHOS
	teste4:		CMP [SI-1],BL
			JNE teste5
			INC VIZINHOS
	teste5:		CMP [SI+1],BL
			JNE teste6
			INC VIZINHOS
	teste6:		CMP [SI+61],BL
			JNE teste7
			INC VIZINHOS
	teste7:		CMP [SI+62],BL
			JNE teste8
			INC VIZINHOS
	teste8:		CMP [SI+63],BL
			JNE segueobaile
			INC VIZINHOS


			;calcula e salva na matriztemp estado da celula na proxima geracao
	segueobaile:	MOV AL,VIZINHOS
			CMP AL,3
			JZ VIVA
			CMP AL,2
			JZ TEMDOIS
	MORTA:		MOV DL,' '
			MOV [DI],DL
			;MOV DL,VIZINHOS
			;MOV [DI], DL
			;ADD [DI],'0'
			JMP fimCELULA
	
	TEMDOIS:	;MOV AL,' '
			;CBW			; converte AL para AX
			CMP ESTADOATUAL,' '  ;se eh morta, continua morta
			JZ MORTA
	
	VIVA:		MOV DL,'#'
			MOV [DI],DL
			;MOV DL,VIZINHOS
			;MOV [DI], DL
			;ADD [DI],'0'
	
	; preparar proxima avaliacao ou terminar caso linha e coluna findem
	fimCELULA:


			INC SI
			INC DI
			CMP COLUNA, MAXCOLUNA			
			JZ fimCOLUNA
			INC COLUNA
			JMP ANALISA ; vai analisar a proxima celula
	fimCOLUNA:	CMP LINHA, MAXLINHA
			JZ ACABOU
			INC LINHA
			MOV COLUNA,1
			; estes proximos 4 inc´s eh para pular as bordas da matriz
			INC SI
			INC SI
			INC DI
			INC DI
			JMP ANALISA
	
	
	ACABOU:		;vamos copiar a matriztemp para matrizorig (fiz na mao pq rep movsb nao rolou)
			LEA SI, MATRIZTEMP
			LEA DI, MATRIZORIG
			MOV CX,1674		;contador
	copia:		MOV AL, [SI]
			MOV [DI],AL
			INC DI
			INC SI
			DEC CX
			CMP CX,0
			JNE copia			
			
			; posiciona cursor no campo geracao
			mov    dh,4		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)			
	

			;atualizando o contador de geracao
			INC GERACAO
			
			STD
			MOV AX,geracao
			LEA DI,convertido+3
			CALL edita

			LEA DX,convertido	
			SUB DX, 6	;devido lixo bom
			CALL WRITE

		
			; reposiciona cursor no campo entrada
			mov    dh,0		; linha zero  
			mov    dl,0		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int	10h
	
			RET
PASSAGERACAO ENDP 


DEFINETEMPORIZADOR	PROC NEAR

			
	de_novot:	;limpa entrada
			; posiciona cursor no campo entrada
			mov    dh,21		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			; printa branco
			lea    dx,branco ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS
			; posiciona cursor no campo entrada
			mov    dh,21		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)

			mov bl,0
			; lê
			lea    di, tempo
	entradat:	mov    ah,1
			int    21h	; le um caracter com eco
			cmp    al,CR   ; compara com carriage return
			je     continuat
			cmp    al,8   ; compara com backspace
			je     backspacet
			cmp    bl,2   ; se digitou terceiro digito, temporizador invalido
			je     de_novot         
			mov    [di],al ; coloca no buffer
			inc    di
			inc	bl
			jmp    entradat
	
	backspacet:	dec di
			mov dl,' '
			mov ah,2
			int 21h
			mov dl,8
			mov ah,2
			int 21h
			jmp    entradat

	continuat:	mov   byte ptr [di],0  ; forma string ASCIIZ com o nome do arquivo
			lea si,tempo
			mov al,[si]
			sub al,'0'
			mov dl,10
			imul dl
			mov bl,[si+1]
			sub bl,'0'
			add al,bl
			cbw
			mov tempoint,ax
			
			; printa no temporizador
			; posiciona cursor no campo entrada
			mov    dh,10		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			lea si,tempo
			mov dl,[si]
			mov ah,2
			int 21h
			inc si
			mov dl,[si]
			mov ah,2
			int 21h		

			RET		
DEFINETEMPORIZADOR	ENDP


LEARQUIVO	PROC NEAR
			MOV TEMPOINT,0
			; posiciona cursor no campo entrada
			mov    dh,10		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			mov dl,'0'
			mov ah,2
			int 21h
			inc si
			mov dl,'0'
			mov ah,2
			int 21h		

			lea di,nome
			mov al,' '
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al



			;limpa entrada
			; posiciona cursor no campo entrada
			mov    dh,21		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			; printa branco
			lea    dx,branco ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS


			; posiciona cursor no campo entrada
	de_novo:	mov    dh,21		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)


			; le nome do arquivo
			lea    di, nome
	entrada:	mov    ah,1
			int    21h	; le um caracter com eco
			cmp    al,CR   ; compara com carriage return
			je     continua
			cmp    al,8   ; compara com backspace
			je     backspace         
			mov    [di],al ; coloca no buffer
			inc    di
			jmp    entrada
	
	backspace:	dec di
			mov dl,' '
			mov ah,2
			int 21h
			mov dl,8
			mov ah,2
			int 21h
			jmp    entrada

	continua:	mov   byte ptr [di],0  ; forma string ASCIIZ com o nome do arquivo

			; abre arquivo para leitura 
			mov    ah,3dh
			mov    al,0
			lea    dx,nome
			int 21h
			jnc    abriu_ok
			;se chegou aqui deu erro. printa mensagem
			mov    dh,23		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
		        LEA DX, msgerro	
		        CALL WRITE						
			jmp    de_novo

	abriu_ok:	mov handler,ax
			;apaga mensagens
			mov    dh,23		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			; printa branco
			lea    dx,branco ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS


			;reposiciona cursor
			mov    dh,0		; linha zero  
		        mov    dl,0		; coluna zero
		        mov    bh,0		; numero da pagina (zero = primeira)
		        mov    ah,2            ; set cursor position
		        int    10h 


			;prepara matrizorig
			lea SI,matrizorig
			add SI,63		; primeira celula. pula as bordas
	
	laco:		; le um caracter do arquivo
			mov ah,3fh
			mov bx,handler
			mov cx,1
			lea dx,buffer
			int 21h
         
			; escreve caracter na tela
			cmp ax,cx
			jne fim
			mov dl, buffer
			cmp dl,'.'
			jne ehvivo2
			mov dl,' '
	ehvivo2:	mov ah,2
			int 21h
	
			; nao armazeno em memoria LF nem CR
			mov dl, buffer	 
		        cmp dl, LF
		        je fimCOLUNA1
			mov dl, buffer	 
		        cmp dl, CR
		        je laco
		
			mov AL,buffer
			cmp al,'.'
			jne ehvivo
			mov al,' '
	ehvivo:		MOV [SI],AL	
			INC SI
			JMP laco

	fimCOLUNA1:	add SI,2
			JMP laco

	
	fim:		mov ah,3eh	 ; fecha arquivo
			mov bx,handler
			int 21h


			; e posiciona cursor
			mov    dh,1		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			; printa branco
			lea    dx,branco ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS

			;escreve nome
			; e posiciona cursor
			mov    dh,1		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			
		        LEA DX, NOME	
		        CALL WRITE


			;limpa entrada
			; posiciona cursor no campo entrada
			mov    dh,4		;LINHA  
			mov    dl,63		; coluna
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			; printa branco
			lea    dx,geracaotxt ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS


			MOV GERACAO,0
			lea di,convertido
			MOV AL,'0'
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al

			lea di,lixobom
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al
			inc di
			mov [di],al


	 RET
LEARQUIVO ENDP


MONTAMATRIZES PROC NEAR
			LEA SI,MATRIZORIG
			LEA DI,MATRIZTEMP
			MOV LINHA,1
			MOV COLUNA,1
	borda1:		MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, [SI]  ; escreve caracter na tela
;			mov ah,2
;			int 21h




			CMP COLUNA, MAXCOLUNA+2			
			JZ meiomatriz
			INC COLUNA
			INC SI
			INC DI
			JMP borda1
	
	meiomatriz:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, CR  ; escreve caracter na tela
;			mov ah,2
;			int 21h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, LF  ; escreve caracter na tela
;			mov ah,2
;			int 21h




			;pinta lateral esquerda matriz na linha
			INC SI
			INC DI
			MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, [SI]  ; escreve caracter na tela
;			mov ah,2
;			int 21h





			MOV COLUNA,1
	blabla:		INC SI
			INC DI


			MOV DL,'@'
			MOV [DI],DL
			MOV DL,'@'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, [SI]  ; escreve caracter na tela
;			mov ah,2
;			int 21h




			CMP COLUNA, MAXCOLUNA
			JZ testaLinha
			INC COLUNA
			JMP blabla
							
	testaLinha:	;pinta lateral direita matriz
			INC SI
			INC DI
			MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, [SI]  ; escreve caracter na tela
;			mov ah,2
;			int 21h


			;testa linha
			CMP LINHA, MAXLINHA
			JZ fimMontaMatriz
			INC LINHA
			MOV COLUNA,1
			JMP meiomatriz

	fimMontaMatriz:

			MOV COLUNA,1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, CR  ; escreve caracter na tela
;			mov ah,2
;			int 21h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, LF  ; escreve caracter na tela
;			mov ah,2
;			int 21h



	borda2:		INC SI
			INC DI
			MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			mov dl, [SI]  ; escreve caracter na tela;
;			mov ah,2
;			int 21h


			CMP COLUNA, MAXCOLUNA+2			
			JZ fimzao
			INC COLUNA
			INC SI
			INC DI
			JMP borda2

fimzao:
			RET
MONTAMATRIZES ENDP


MOSTRAMATRIZORIG PROC NEAR
			MOV COLUNA,0
			MOV LINHA, 0
			;LEA SI,MATRIZORIG
			LEA SI,MATRIZTEMP
			ADD SI, 63
			MOV CONTADOR,1500

			
			

	;mostra na tela
	mostraorig:
			
			CMP COLUNA,MAXCOLUNA
			JNZ SEMQUEBRALINHA		
			CMP LINHA,MAXLINHA
			JE MatrizAcabou
			
			;pula linha
			mov dl, CR
			mov ah,2
			int 21h
			mov dl, LF
			mov ah,2
			int 21h

			; espera pela digitacao de uma tecla
			;mov ah,8	 
			;int 21h


			mov COLUNA, 0
			INC LINHA
			;pula as bordas
			ADD SI,2	
	SEMQUEBRALINHA:	mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h

			inc SI
			INC COLUNA			
			dec CONTADOR
						
			CMP CONTADOR,0
			JNZ mostraorig

	MatrizAcabou:	RET
MOSTRAMATRIZORIG ENDP





edita    proc
         mov bx,10       ; divisor constante
proximo:
         mov dx,0        ; limpa msbits do dividendo
         div bx          ; divisor de 16 bits -&gt; dividendo de 32 bits em DX:AX
         xchg dx,ax      ; permuta resto (DX) e quociente (AX)
         add  al,'0'     ; transforma resto (valor de 0 a 9) em ASCII
        
	mov [di],al
	dec di
	;stosb           ; guarda caractere na mensaqgem e DECREMENTA DI
         xchg dx,ax      ; devolve quociente para o AX
         test ax,0FFFFH  ; testa se quociente &eacute; zero
         jnz proximo     ; se n&atilde;o for, edita proximo digito
         ret             ; se for, missao cumprida !
edita    endp


	write   proc
			; assume que dx aponta para a mensagem
			mov    ah,9               ; funcao exibir mensagem no AH
			int    21h                ; chamada do DOS
			ret
	write   endp


	PAUSEAR	PROC
			lea    dx,pauseado ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS
			; espera pela digitacao de uma tecla
			mov ah,8	 
			int 21h
			RET
	PAUSEAR ENDP




ESCREVEPASSOAPASSO	PROC

			; posiciona cursor no campo entrada
			mov    dh,7		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)			
	

			LEA DX,ppw
			CALL WRITE

		
			; reposiciona cursor no campo entrada
			mov    dh,0		; linha zero  
			mov    dl,0		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int	10h
			RET
ESCREVEPASSOAPASSO 	ENDP


ESCREVECONTINUO	PROC

			; posiciona cursor no campo entrada
			mov    dh,7		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)			
			; printa branco
			lea    dx,branco ; endereco da mensagem em DX
			mov    ah,9     ; funcao exibir mensagem no AH
			int    21h      ; chamada do DOS
			; posiciona cursor no campo entrada
			mov    dh,7		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)			
	

			LEA DX,continuow
			CALL WRITE

		
			; reposiciona cursor no campo entrada
			mov    dh,0		; linha zero  
			mov    dl,0		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int	10h
			RET
ESCREVECONTINUO 	ENDP


CODIGO  ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Fim Segmento de Codigo ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




			;Montador Posiciona ponteiro das intrucoes
			END START


