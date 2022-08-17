#lang racket

;; Escribe aquí tus soluciones

(define (insertL x y lst)
    )
  
(test-case "insertL"
    (check-equal? (insertL 'x 'y '(x z z x y x))
                  '(y x z z y x y y x)))

(provide (all-defined-out))
