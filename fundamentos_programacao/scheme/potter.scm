;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname aulaaaaaaa) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ())))
;;1

;;cria-matriz-aux: number lista-de-numeros -> lista-de-numbers 
;;funcao auxiliar que a partir de um numero e uma lista, retorna a lista dos n primeiros elementos
;;(cria-matriz-aux 3 (list 1 2 3 4 5 6 7 8 9)) retorna (list 1 2 3)
(define (cria-matriz-aux cont l)
	(cond
		[(empty? l) empty]
		[(> cont 0) (append (list (first l)) (cria-matriz-aux (- cont 1) (rest l)))]
                [else  empty]))

;;elimina-n: number lista -> lista
;;funcao auxiliar que elimina os N primeiros elementos de uma lista
 ;;(elimina-n 3 (list 1 2 3 4 5 6 7 8 9)) retorna (list 4 5 6 7 8 9)

(define (elimina-n n l)
  (cond
    [(empty? l) empty]
    [(> n 0) (elimina-n (- n 1) (rest l))]
    [else l]))


 
;;cria-matriz: number lista-de-numbers -> matriz
;;uma matriz e:
;;ou empty
;;ou (cons ln ma), onde ln eh uma lista de numbers e ma uma matriz
;;(cria-matriz 3 (list 1 2 3 4 5 6 7 8 9)) retorna (list (list 1 2 3)
;;(list 4 5 6) (list 7 8 9))

(define (cria-matriz n lista)
   (cond
     [(empty? lista) empty]
     [else (cons (cria-matriz-aux n lista) (cria-matriz n (elimina-n n lista)))]))

;;2
;; Uma web-page é
;; - empty, ou
;; - (cons s wp), onde s:symbol e wp:web-page, ou
;; - (cons ewp wp), onde ewp:web-page e wp:web-page
;;Um exemplo de web-page é
(define wp1
(list 'The 'TeachScheme 'Web 'Page 'Here 'you 'can 'find:
(list 'LectureNotes 'for 'Teachers)
(list 'Guidance 'for
(list 'DrScheme: 'a 'Scheme 'programming 'environment))
(list 'Exercise 'Sets)
(list 'Solutions 'for 'Exercises)
(list 'For 'further 'information
(list 'email: 'sc@sc.com 'web: 'sc.com))))



;; palavras-niveis-impares-aux: number web-page -> lista-de-symbols
;;dada uma web page, retorna a uma lista contendo as palavras das embebed web-page de nivel impar
;; (palavras-niveis impares-aux 0 (list 'gremio 'campeao (list 'do 'mundo (list 'ontem))) retorna
;; (list 'do 'mundo)


(define (palavra-niveis-impares-aux n wp)
  (cond
    [(empty? wp) empty]
    [(symbol? (first wp)) (cond
       [( = (remainder n 2) 1) (append (list (first wp)) (palavra-niveis-impares-aux n (rest wp)))]
       [else (palavra-niveis-impares-aux n (rest wp))])]
    [(cons? (first wp)) (append (palavra-niveis-impares-aux (+ n 1) (first wp))(palavra-niveis-impares-aux n  (rest wp))) ]))


(define (palavras-niveis-impares wp)
  (palavra-niveis-impares-aux 0 wp))
(palavras-niveis-impares wp1

















