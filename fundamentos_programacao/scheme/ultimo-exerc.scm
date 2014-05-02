;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname ultimo-exerc) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #8(#t constructor repeating-decimal #f #t none #f ())))
(define-struct pw ( h p ))
;(make-pw 'terra (cons (make-pw 'esportes (cons 'futebol (cons 'grenal) empty))))
;; find pw s -> lista-nome-paginas
(define (find pw s)
  (find-aux pw s empty))
;;find-aux pw s lista -> lista-nome-paginas
(define (find-aux pw s l)
  (cond
    [(empty? (pw-p pw)) l]
    [(symbol? (first (pw-p pw))) (testa (pw-p pw) s (cons (pw-h pw) l))]
    [(pw? (first (pw-p pw))) (find-aux (first (pw-p pw)) s (cons (pw-h pw) l))]))
;;testa p s l -> lista ou empty
(define (testa p s l)
  (cond
    [(symbol=? s (first p)) l]
    [(empty? (first (rest p))) empty]
    [(symbol? (first (rest p)))(testa (rest p) s l)]
    [(pw? (first (rest p))) (find-aux (first (rest p)) s l)]))

(find (make-pw 'terra (cons (make-pw 'esportes (cons 'futebol (cons 'grenal empty))) empty )) 'terra)
  