; Jogo da Vida para Intel x86
; 3º Trabalho - Arquitetura de Computadores I
; Professora: Taisy Weber
; Aluno: Germano de Mello Andersson, matr. 137719
; 2008/02




; Segmento de Pilha
PILHA   SEGMENT STACK
	DB 32 DUP ('STACK---')
PILHA   ENDS


; Segmento de Dados
DADOS   SEGMENT

	;constantes
	MAXLINHA	EQU	25
	MAXCOLUNA	EQU	60
	CR		EQU	0DH ; carriage return
	LF		EQU	0AH ; line feed


	;variaveis
	MENSAGEM DB 'Hello World!', 0DH, 0AH
	TAMANHO EQU $-MENSAGEM
	CONTADOR DW ?
	GERACAO		DB	?
	LINHA		DB	1
	COLUNA		DB	1
	VIZINHOS	DW	0
	MATRIZORIG	DB	1674 DUP (0)
	MATRIZTEMP	DB	1674 DUP (0)
	indiceorig	DW	?
	indicetemp	DW	?
	ESTADOATUAL	DW	?
	num		db	0

	nome dB 64 dup(?)
	buffer dB 128 dup(?)
	pede_nome dB 'Nome do arquivo: ','$'
	erro dB 'Erro! Repita.',CR,LF,'$'
	msg_final dB 'Fim do programa.',CR,LF,'$'
	handler dw ?

DADOS   ENDS


; Segmento de Codigo
CODIGO  SEGMENT
	ASSUME CS: CODIGO, SS: PILHA, DS: DADOS
	

	;Programa Principal
	START:		MOV AX, DADOS    ; Inicializa segmento de dados
			MOV DS, AX

			CALL MONTAMATRIZES
			CALL LEARQUIVO
			CALL PASSAGERACAO
			CALL MOSTRAMATRIZORIG


			;Fim do Programa
			MOV AH, 4CH ; Retorna ao DOS
			INT 21H


PASSAGERACAO	PROC NEAR

			; prepara variaveis
			MOV LINHA,1
			MOV COLUNA,1
			
			;posiciona ponteiro na primeira celula valida 
			LEA SI, MATRIZORIG
			LEA DI, MATRIZTEMP
			ADD SI, 61
			ADD DI, 61
			MOV DX,[SI]
			MOV ESTADOATUAL,DX

	ANALISA:	;vamos verificar quantos vizinhos vivos
			MOV VIZINHOS,0
			MOV AX,VIZINHOS
			ADD AX,[SI-61]
			ADD AX,[SI-60]
			ADD AX,[SI-59]
			ADD AX,[SI-1]
			ADD AX,[SI+1]
			ADD AX,[SI+59]
			ADD AX,[SI+60]
			ADD AX,[SI+61]
			
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
; pede nome do arquivo
de_novo: lea    dx,pede_nome ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
; le nome do arquivo
         lea    di, nome
entrada: mov    ah,1
         int    21h	; le um caracter com eco
         cmp    al,CR   ; compara com carriage return
         je     continua
         mov    [di],al ; coloca no buffer
         inc    di
         jmp    entrada
continua: mov   byte ptr [di],0  ; forma string ASCIIZ com o nome do arquivo
         mov    dl,LF   ; escreve LF na tela
         mov    ah,2
         int    21h
;
; abre arquivo para leitura 
         mov    ah,3dh
         mov    al,0
         lea    dx,nome
         int 21h
         jnc    abriu_ok
         lea    dx,erro  ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         jmp    de_novo
;
abriu_ok: mov handler,ax

			;prepara matrizorig
			MOV LINHA,1
			MOV COLUNA,1
			lea SI,matrizorig
			add SI,61
	
laco:    mov ah,3fh      ; le um caracter do arquivo
         mov bx,handler
         mov cx,1
         lea dx,buffer
         int 21h
         cmp ax,cx
         jne fim
;TEST         mov dl, buffer  ; escreve caracter na tela
;         mov ah,2
;         int 21h

			;armazena caracter em matrizorig
			mov AL,buffer
			MOV [SI],AL	

			; verifica caso linha e coluna findem
			INC SI
			CMP COLUNA, MAXCOLUNA			
			JZ fimCOLUNA1
			INC COLUNA
			JMP naTela
fimCOLUNA1:		CMP LINHA, MAXLINHA
			JZ naTela
			INC LINHA
			MOV COLUNA,1
			; estes proximos 2 inc´s pulam as bordas da matriz
			INC SI 
			INC SI
		


         
naTela:  mov dl, buffer	 ; escreve na tela até encontrar um LF (fim de linha)
         cmp dl, LF
         jne laco
;   
;         mov ah,8	 ; espera pela digitacao de uma tecla qualquer
;         int 21h
	 
	 MOV COLUNA,1	; para acertar


         cmp dl, CR
	 jne laco
		 MOV COLUNA,1	; para acertar	 

         jmp laco
;
fim:     mov ah,3eh	 ; fecha arquivo
         mov bx,handler
         int 21h
;      
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
			mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h




			CMP COLUNA, MAXCOLUNA+2			
			JZ meiomatriz
			INC COLUNA
			INC SI
			INC DI
			JMP borda1
	
	meiomatriz:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, CR  ; escreve caracter na tela
			mov ah,2
			int 21h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, LF  ; escreve caracter na tela
			mov ah,2
			int 21h




	;pinta lateral esquerda matriz na linha
			INC SI
			INC DI
			MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h





			MOV COLUNA,1
	blabla:		INC SI
			INC DI


			MOV DL,'@'
			MOV [DI],DL
			MOV DL,'@'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h




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
			mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h


			;testa linha
			CMP LINHA, MAXLINHA
			JZ fimMontaMatriz
			INC LINHA
			MOV COLUNA,1
			JMP meiomatriz

	fimMontaMatriz:

			MOV COLUNA,1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, CR  ; escreve caracter na tela
			mov ah,2
			int 21h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, LF  ; escreve caracter na tela
			mov ah,2
			int 21h



	borda2:		INC SI
			INC DI
			MOV DL,'.'
			MOV [DI],DL
			MOV DL,'.'
			MOV [SI],DL

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h


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
			MOV COLUNA,1
			;LEA SI,MATRIZORIG
			;LEA SI,MATRIZTEMP
			MOV CONTADOR,1674

	mostraorig:	;mostra na tela
			
			CMP COLUNA,MAXCOLUNA+2
			JNZ SEMQUEBRALINHA		
		
			;mov dl, CR  ; escreve caracter na tela
			;mov ah,2
			;int 21h
			;mov dl, LF  ; escreve caracter na tela
			;mov ah,2
			;int 21h
			mov COLUNA, 1		
		
	SEMQUEBRALINHA:	mov dl, [SI]  ; escreve caracter na tela
			mov ah,2
			int 21h
			
			inc SI
			INC COLUNA			
			dec CONTADOR
						
			CMP CONTADOR,0
			JNZ mostraorig

			RET
MOSTRAMATRIZORIG ENDP






CODIGO  ENDS
	END START


