         assume cs:codigo,ds:dados,es:dados,ss:pilha

CR        EQU    0DH ; caractere ASCII &quot;Carriage Return&quot; 
LF        EQU    0AH ; caractere ASCII &quot;Line Feed&quot;

; SEGMENTO DE DADOS DO PROGRAMA
dados     segment
caractere db ?
pede_key  db 'Digite uma tecla (^C para terminar): ','$'
second    db 'Tecla estendida. Lendo segundo byte...',CR,LF,'$'
msg_final db 'Fim do programa.',CR,LF,'$'
total     dw 0     ; contador de caracteres
espacos   dw 0     ; contador de espacos em branco
ceerres   dw 0     ; contador de CRs
eleefes   dw 0     ; contador de LFs
resposta  db CR,LF,'Voce digitou: ','$'
hexa      db ' (hexa: ','$'
fecha     db 'H)',Cr,LF,'$'
dados     ends

; SEGMENTO DE PILHA DO PROGRAMA
pilha    segment stack ; permite inicializacao automatica de SS:SP
         dw     128 dup(?)
pilha    ends
         
; SEGMENTO DE C&Oacute;DIGO DO PROGRAMA
codigo   segment
inicio:         ; CS e IP sao inicializados com este endereco
         mov    ax,dados           ; inicializa DS
         mov    ds,ax              ; com endereco do segmento DADOS
         mov    es,ax              ; idem em ES
; fim da carga inicial dos registradores de segmento
;
; pede nome do arquivo
le_key:  lea    dx,pede_key ; endereco da mensagem em DX
         mov    ah,9         ; funcao exibir mensagem no AH
         int    21h          ; chamada do DOS
entrada: mov    ah,1
         int    21h	     ; le um caractere com eco

         mov    caractere,al ; guarda caractere
         lea    dx,resposta
         mov    ah,9
         int    21h
         mov 	dl, caractere  ; escreve caractere na tela
         mov 	ah,2
         int 	21h         
         lea    dx,hexa
         mov    ah,9
         int    21h
         mov    al, caractere
         shr    al, 4
         and    al, 0fH
         cmp    al, 10
         jl     digitom
         sub    al,9
         or     al,40H
         jmp    imprimem
digitom: or     al, 30H
imprimem:mov    dl, al
         mov 	ah,2
         int 	21h 

         mov    al, caractere
         and    al, 0fH
         cmp    al, 10
         jl     digitol
         sub    al,9
         or     al,40H
         jmp    imprimel
digitol: or     al, 30H
imprimel:mov    dl, al
         mov 	ah,2
         int 	21h 
         lea    dx, fecha
         mov    ah,9
         int    21h
         cmp    caractere,0  ; compara com zero
         jne    le_key   ; se nao for, le outro caracter
         lea    dx,second
         mov    ah,9
         int    21h
         jmp    entrada
         
;

; fim 
;      
         lea    dx,msg_final ; endereco da mensagem em DX
         mov    ah,9     ; funcao exibir mensagem no AH
         int    21h      ; chamada do DOS
         mov    ax,4c00h ; funcao retornar ao DOS no AH
                         ; codigo de retorno 0 no AL
         int    21h      ; chamada do DOS



codigo   ends
         end    inicio
