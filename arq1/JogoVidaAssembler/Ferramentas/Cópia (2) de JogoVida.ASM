; Jogo da Vida para Intel x86
; 3º Trabalho - Arquitetura de Computadores I
; Professora: Taisy Weber
; Aluno: Germano de Mello Andersson, matr. 137719
; 2008/02




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Inicio Segmento de Pilha ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PILHA   SEGMENT STACK
	DB 32 DUP ('STACK---')
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
	CONTADOR DW ?
	GERACAO		DB	?
	LINHA		DB	1
	COLUNA		DB	1
	VIZINHOS	DW	0
	MATRIZORIG	DB	1674 DUP (0),'$'
	MATRIZTEMP	DB	1674 DUP (0),'$'
	indiceorig	DW	?
	indicetemp	DW	?
	ESTADOATUAL	DW	?
	num		db	0
	convertido	db	'    ','$'	 ; memoria com resultado da conversao binario to asc
	arqtelainicial  db	'tela1.txt',0H

	nome		dB	10 dup(?),'$'
	buffer		dB	128 dup(?),'$'
	handler		dw	?
	matrizok	db	0


DADOS   ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Fim Segmento de Dados ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Inicio Segmento de Codigo ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
CODIGO  SEGMENT
	ASSUME CS: CODIGO, SS: PILHA, DS: DADOS, ES: DADOS
	

	;### Programa Principal ###
	START:		MOV AX, DADOS    ; Inicializa segmento de dados
			MOV DS, AX
			
			
			;prepara menus
			;CALL TELAINICIAL
			;prepara borda das matrizes na memoria
			;CALL MONTAMATRIZES
			
			;meus testes
			CALL MONTAMATRIZES
			CALL LEARQUIVO
			CALL MOSTRAMATRIZORIG
			JMP SairPrograma

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

	PassoAPasso:	CALL PASSAGERACAO
			JMP AguardaTecla
	
	AlteraTimer:	
			JMP AguardaTecla

	Rodar:		
			JMP AguardaTecla


	SairPrograma:	MOV AH, 4CH ; Retorna ao DOS
			INT 21H




;### Sub-rotina Imprime tela inicial ###
	TELAINICIAL PROC NEAR
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
			MOV DX,[SI]
			MOV ESTADOATUAL,DX

	ANALISA:	;vamos verificar quantos vizinhos vivos
			MOV VIZINHOS,0
			MOV AX,VIZINHOS
			ADD AX,[SI-63]
			ADD AX,[SI-62]
			ADD AX,[SI-61]
			ADD AX,[SI-1]
			ADD AX,[SI+1]
			ADD AX,[SI+61]
			ADD AX,[SI+62]
			ADD AX,[SI+63]
			
			;calcula e salva na matriztemp estado da celula na proxima geracao
			CMP AX,3
			JZ VIVA
			CMP AX,2
			JZ TEMDOIS
	MORTA:		MOV DL,'.'
			MOV [DI],DL
			JMP fimCELULA
	TEMDOIS:	CMP ESTADOATUAL,'.'  ;se eh morta, continua morta
			JZ MORTA
	VIVA:		MOV DL,'#'
			MOV [DI],DL
	
	; preparar proxima avaliacao ou terminar caso linha e coluna findem
	fimCELULA:

;teste
;	mov dl, [SI]  ; escreve caracter na tela
;			mov ah,2
;			int 21h
;fim teste

			INC SI
			INC DI
			CMP COLUNA, MAXCOLUNA			
			JZ fimCOLUNA
			INC COLUNA
			JMP entaoANALISA ; vai analisar a proxima celula
	fimCOLUNA:	CMP LINHA, MAXLINHA
			JZ ACABOU
			INC LINHA
			MOV COLUNA,1
			; estes proximos 4 inc´s eh para pular as bordas da matriz
			INC SI
			INC SI
			INC DI
			INC DI
			JMP entaoANALISA
	
	entaoANALISA:   JMP ANALISA

	ACABOU:		;vamos copiar a matriztemp para matrizorig

			RET
PASSAGERACAO ENDP 



LEARQUIVO	PROC NEAR



			; posiciona cursor no campo entrada
	de_novo:	mov    dh,22		; linha zero  
			mov    dl,63		; coluna zero
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
			jmp    entrada

	continua:	mov   byte ptr [di],0  ; forma string ASCIIZ com o nome do arquivo

			; abre arquivo para leitura 
			mov    ah,3dh
			mov    al,0
			lea    dx,nome
			int 21h
			jnc    abriu_ok
			jmp    de_novo

	abriu_ok:	mov handler,ax

			;reposiciona cursor
			mov    dh,0		; linha zero  
		        mov    dl,0		; coluna zero
		        mov    bh,0		; numero da pagina (zero = primeira)
		        mov    ah,2            ; set cursor position
		        int    10h 


			;prepara matrizorig
			MOV LINHA,0
			MOV COLUNA,0
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
			;mov dl, buffer
			;mov ah,2
			;int 21h

			;pula armazenamento na memoria se ja concluido
			CMP matrizok,1
			JE laco
			
			; nao armazeno em memoria LF nem CR
			mov dl, buffer	 
		        cmp dl, LF
		        je laco
			mov dl, buffer	 
		        cmp dl, CR
		        je laco
			

			;armazena caracter em matrizorig
			CMP COLUNA, MAXCOLUNA
			JZ fimCOLUNA1
			
			mov AL,buffer
			MOV [SI],AL	
			INC SI
			INC COLUNA
			JMP laco

	fimCOLUNA1:			
			mov AL,buffer
			MOV [SI],AL	
			INC SI
			CMP LINHA, MAXLINHA+2
			JZ MatrizJaOk
			INC LINHA
			MOV COLUNA,0
			; pula as bordas da matriz
			ADD SI,1
			JMP laco

	MatrizJaOk:	MOV matrizok,1


	fim:		mov ah,3eh	 ; fecha arquivo
			mov bx,handler
			int 21h


			;escreve nome
			; e posiciona cursor
			mov    dh,2		; linha zero  
			mov    dl,63		; coluna zero
			mov    bh,0		; numero da pagina (zero = primeira)
			mov    ah,2            ; set cursor position
			int    10h             ; chamada BIOS (video)
			
		        LEA DX, NOME	
		        CALL WRITE

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
			LEA SI,MATRIZORIG
			ADD SI, 63
			MOV CONTADOR,1500

			
			;pula linha
			mov dl, CR
			mov ah,2
			int 21h
			mov dl, LF
			mov ah,2
			int 21h

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
			mov ah,8	 
			int 21h


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




; subrotina para editar (converter de bin&aacute;rio para ASCII 
; com 4 digitos e colocar na mensagem) um valor de 16 bits
; de um contador (pressupoe que mensagem contenha espacos)
; recebe em DI endereco do byte das unidades na mensagem
; recebe em AX o valor do contador
; usa divis&atilde;o de 16 bits para evitar overflow na divis&atilde;o por 10
edita    proc
         mov bx,10       ; divisor constante
proximo:
         mov dx,0        ; limpa msbits do dividendo
         div bx          ; divisor de 16 bits -&gt; dividendo de 32 bits em DX:AX
         xchg dx,ax      ; permuta resto (DX) e quociente (AX)
         add  al,'0'     ; transforma resto (valor de 0 a 9) em ASCII
         stosb           ; guarda caractere na mensaqgem e DECREMENTA DI
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


CODIGO  ENDS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Fim Segmento de Codigo ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




			;Montador Posiciona ponteiro das intrucoes
			END START


