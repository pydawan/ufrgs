;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname lab6-3) (read-case-sensitive #t) (teachpacks ((lib "world.ss" "teachpack" "htdp"))) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ((lib "world.ss" "teachpack" "htdp")))))
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
