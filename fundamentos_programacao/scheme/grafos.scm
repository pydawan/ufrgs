;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname grafos) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ())))
(define-struct link (src valor tgt))
;;grafo é
;; ou empty
;; ou (cons link grafo)

(cons (make-link 'b 5 'a) (cons (make-link 'a 10 'c) (cons (make-link 'a 20 'g) (cons (make-link 'g 30 'd) (cons (make-link 'd 12 'b) (cons (make-link 'e 3 'e) empty))))))

;;encontra-rota: grafo symbol symbol -> grafo ou false
;;testa-rota: lista-grafos symbol symbol -> grafo ou false
;;encontra-src: grafo symbol -> lista-grafos
;;armazena-rota: link grafo -> grafo
;;tem-loop: lista symbol -> boolean
;;retorna-src: link -> symbol
;;retorna-tgt: link -> symbol

(define (encontra-rota g src tgt)
  (cond
    [(empty? g)empty]
    [else (testa-rota (encontra-src g src) src tgt)]))

(define (testa-rota lg src tgt ls)
  (cond
    [(empty? lg)false]
    [(tem-loop ls (retorna-tgt (first lg))) (testa-rota (rest lg) src tgt ls)]
    [(=symbol? (retorna-src (first lg)) src) (armazena-rota (first (first lg)) (testa-rota (cons (rest (first lg)) (rest lg)) (retorna-src  
    ;;complicou!! :p
                                                                                                                               
                                                                                                                           