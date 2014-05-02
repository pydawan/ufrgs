;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname testando-lab5) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ())))
;;1
;; cria-matriz n lista -> matriz
;; recebe um numero n e uma lista e cria uma matriz com listas de n numeros
;; onde matriz é
;; ou empty
;; ou (cons lista matriz)
(define (cria-matriz n l)
  (cond
    [(empty? l) empty]
    [else (cons (cria-lista n l) (cria-matriz n (lista-menor n l)))]))


(define (cria-lista n l)
  (cond
    [(empty? l) empty]
    [(= n 0) empty]
    [else (append (list (first l)) (cria-lista (- n 1) (rest l)))]))

(define (lista-menor n l)
  (cond
    [(> n 0) (lista-menor (- n 1) (rest l))]
    [else l]))


;;(cria-matriz 2 (list 1 2 3 4))


;;2
;;Exemplo de web page
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

;;palavra-niveis-impares wp -> lista
;; recebe uma wp e retorna a lista das palavras que ocorrem diretamente nas suas ewp de nível ímpar.

;;onde wp é
;; ou empty
;; ou (cons symbol wp) 
;; ou (cons ewp wp)
;; onde ewp é wp (ewp é uma wp dentro de outra wp)

(define (palavra-niveis-impares wp)
  (cond
    [(empty? wp)empty]
    [(cons? (first wp)) (append (auxiliar (first wp) 1) (palavra-niveis-impares (rest wp)))]
    [else (palavra-niveis-impares (rest wp))]))

;;auxiliar wp n -> lista
;; recebe uma wp e um nivel e retorna uma lista de palavras(symbols) que está no nível impar
(define (auxiliar wp n)
  (cond
    [(empty? wp)empty]
    [(cons? (first wp))(auxiliar (rest wp) (+ n 1))]
    [(eh-impar n)
                   (cond
                     [(symbol? (first wp)) (append (list (first wp)) (auxiliar (rest wp) n))]
                     [else (auxiliar (rest wp) n)])
    ]
    [else (auxiliar (rest wp) n)]))

;;eh-impar n -> boolean
;; recebe um numero e retorna true se impar e false se par
(define (eh-impar n)
  (cond
  [(= 1 (remainder n 2)) true]
  [else false]))

;;(palavra-niveis-impares wp1)

;3
(define-struct nodo (filhos numeros))
;; Uma an (arvore-de-numeros) é uma estrutura
;; (make-nodo f n), onde f:lista-de-an e n:lista-de-num
;; Uma lista-de-an é
;; ou empty
;; ou (cons a l), onde   a:an  e  l:lista-de-an
;; Uma lista-de-num
;; - empty, ou
;; - (cons n l), onde  n:number e l:lista-de-num

;;3    
(define-struct nodo (filhos numeros))
;;soma lista -> number
;;recebe uma lista e devolve a soma de todos numeros
(define (soma l)
  (cond
    [(empty? l) 0]
    [else (+ (first l) (soma (rest l)))]))

;;cont lista -> number
;; recebe uma lista e devolve o numero de elementos
(define (cont l)
  (cond
    [(empty? l) 0]
    [else (+ 1 (cont (rest l)))]))

;; lista-unica an -> lista
;; recebe uma arvore de numeros e devolve uma lista com todos numeros desta arvore
(define (lista-unica an)
  (cond
    [(empty? (nodo-filhos an)) (nodo-numeros an)]
    [else (append (nodo-numeros an) (lista-unica (first (nodo-filhos an))))]))
;;media-an an -> number
;;recebe uma arvore de numeros e devolve a media aritmetica da soma de todos numeros
(define (media-an an)
  (/ (soma (lista-unica an)) (cont (lista-unica an))))

(media-an (make-nodo (list (make-nodo (list (make-nodo empty (list 2 2 2))) (list 2 2 2))) (list 2 2 2)))


    
























