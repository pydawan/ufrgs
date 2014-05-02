;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname |lista scheme ultima|) (read-case-sensitive #t) (teachpacks ((lib "draw.ss" "teachpack" "htdp"))) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ((lib "draw.ss" "teachpack" "htdp")))))
;;tira_n: numero lista_de_numeros -> lista_de_numeros

;;recebe um numero n e uma lista de numeros, e retorna uma lista de numeros sem os n
;;primeiros numeros.

(define (tira_n n lista)
  (cond
    [(empty? lista) empty]
    [(> n 0) (tira_n (- n 1) (rest lista))]
    [else (cons (first lista) (tira_n n (rest lista)))]))

;;cria lista: numero lista_de_numeros -> lista_de_numeros

;;recebe um numero n e uma lista de numeros e retorna uma lista com os n primeiros
;;elementos da lista.

;;exemplo (cria_lista 3 (list 1 2 3 4 5 6)) -> (list 1 2 3)

(define (cria_lista n lista)
  (cond
    [(empty? lista) empty]
    [(= 0 n) empty]
    [else (cons (first lista) (cria_lista (- n 1) (rest lista)))]))

;;cria matriz: numero, lista de numeros -> lista de lista de numeros

;;recebe um numero n e uma lista contendo n² numeros, e retorna uma matriz.

;;exemplo: (cria-matriz 2 (list 1 2 3 4)) deve produzir (list (list 1 2)
;;(list 3 4))

(define (cria_matriz n lista)
  (cond
    [(empty? lista) empty]
    [else (cons (cria_lista n lista) (cria_matriz n (tira_n n lista)))]))
;;=================================================================================================================================
;;exercicio 2:

(define wp1
(list 'The 'TeachScheme 'Web 'Page
'Here 'you 'can 'find:
(list 'LectureNotes 'for 'Teachers)
(list 'Guidance 'for
(list 'DrScheme: 'a 'Scheme 'programming 'environment))
(list 'Exercise 'Sets)
(list 'Solutions 'for 'Exercises)
(list 'For 'further 'information
(list 'email: 'sc@sc.com 'web: 'sc.com))))

;;faz-lista: numero lista -> lista

;;recebe uma numero n e uma lista. Retorna uma lista se n for impar.

(define (faz-lista n web)
  (cond
    [(empty? web) empty]
    [(cons? (first web)) (append (faz-lista (+ 1 n) (first web)) (faz-lista n (rest web)))]
    [(not (= (remainder n 2) 0)) (cons (first web) (faz-lista n (rest web)))]
    [else (faz-lista n (rest web))]))

;;palavras-niveis-impares: web-page -> lista-simbolos

;;dada uma web-page, retorna a lista das palavras
;;que ocorrem diretamente nas suas embedded web-pages de nível ímpar.

;;exemplo: (palavras-niveis-impares wp1) ==>
;;(list ’LectureNotes ’for ’Teachers ’Guidance ’for ’Exercise ’Sets
;;’Solutions ’for ’Exercises ’For ’further ’information)

(define (palavras-niveis-impares web)
  (cond
    [(empty? web) empty]
    [(not (cons? (first web))) (palavras-niveis-impares (rest web))]
    [else (append (faz-lista 1 (first web)) (palavras-niveis-impares (rest web)))]))
;;================================================================================================
;;exercicio 3

(define-struct nodo (filhos numeros))
;; Uma an (arvore-de-numeros) é uma estrutura
;;(make-nodo f n), onde f:lista-de-an e n:lista-de-num
;; Uma lista-de-an é
;; - empty, ou
;; - (cons a l), onde a:an e l:lista-de-an
;; Uma lista-de-num
;; - empty, ou
;; - (cons n l), onde n:number e l:lista-de-num

;;soma-nodos: lista-an -> numero
;;recebe uma lista de arvores de numeros e rotorna a soma das mesmas.
(define (soma-nodos lista-nd)
  (cond
    [(empty? lista-nd) 0]
    [else (+ (soma (first lista-nd)) (soma-nodos (rest lista-nd)))]))
;;soma-lista: lista de numeros-> numero
;;recebe uma lista de numeros e retorna a soma dos mesmos.
(define (soma-lista lista)
  (cond
    [(empty? lista) 0]
    [else (+ (first lista) (soma-lista (rest lista)))]))
;;soma: an -> numero
;;recebe uma arvore de numeros e retorna a soma dos numeros desta.
(define (soma an)
  (+ (soma-lista (nodo-numeros an)) (soma-nodos (nodo-filhos an))))

;;numero-nodos: lista-arvores -> numero
;recebe uma lista de arvores de numeros e retorna qntos numeros tem essa lista.
(define (numero-nodos lista-nd)
  (cond
    [(empty? lista-nd) 0]
    [else (+ (numero (first lista-nd)) (numero-nodos (rest lista-nd)))]))
;;numero-lista: lista de numeros-> numero
;;recebe uma lista de numeros e retorna qntos numeros tem nessa lista
(define (numero-lista lista)
  (cond
    [(empty? lista) 0]
    [else (+ 1 (numero-lista (rest lista)))]))
;;numero: arvore-de-numeros -> numero
;;recebe uma arvore de numeros e retorna qntos numeros tem nessa arvore.
(define (numero an)
  (+ (numero-lista (nodo-numeros an)) (numero-nodos (nodo-filhos an))))   
   
;;media-an: an -> numero

;;dada uma árvore de números, retorna a média de todos os números
;;contidos nesta.

;;exemplo (media-an (make-nodo (list (make-nodo empty (list 6 6 6))) (list 6 6 6)) => 6.

(define (media-an an)
  (/ (soma an) (numero an)))
;;======================================================================================================
;;exercicio 4

;; sierpinski : posn posn posn -> true
;; desenha um triângulo de Sierpinski com vértices nos pontos passados como
;; argumentos, e devolve true. Se triângulo passado como argumento tiver
;; dimensões muito pequenas, nada é desenhado.
(define (sierpinski a b c)
  (cond
    [(too-small? a b c) true]
    [else
     (local ((define a-b (mid-point a b))
             (define b-c (mid-point b c))
             (define c-a (mid-point a c)))
       (and
        (draw-triangle a b c)
        (sierpinski a a-b c-a)
        (sierpinski b a-b b-c)
        (sierpinski c c-a b-c)))]))
;; mid-point : posn posn -> posn
;; computa o ponto médio entre os 2 pontos passados como argumentos
;; exemplos: ...
(define (mid-point a-posn b-posn)
  (make-posn
   (mid (posn-x a-posn) (posn-x b-posn))
   (mid (posn-y a-posn) (posn-y b-posn))))
;; mid : number number -> number
;; computa a média entre os números passados como argumento
;; exemplos: (mid 4 2) -> 4
(define (mid x y)
  (/ (+ x y) 2))

;; draw triangle : posn posn posn -> true
;;recebe 3 pontos dezenha um triangulo e retorna true.
(define (draw-triangle a b c)
  (and (draw-solid-line a b 'red) (draw-solid-line b c 'red) (draw-solid-line c a 'red)))
;; too-small? : posn posn posn -> bool
;; recebe 3 pontos e retorna true c a distancia entre eles for menor que 2.

(define (too-small? a b c)
  (cond
    [(< (sqrt (+ (sqr (- (posn-x a) (posn-x b))) (sqr (- (posn-y a) (posn-y b))))) 0.1) true]
    [else false]))

(define A (make-posn 200 0))
(define B (make-posn 27 300))
(define C (make-posn 373 300))
(start 400 350)
(sierpinski A B C)

  
 

