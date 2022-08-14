#lang racket

;; 1.
(define pi 3.14)

;; 2.
(define (area-circle r)
  (-> integer? integer?)
  (* pi (pow2 r)))

(define (pow2 y)
  (-> integer?)
  (expt y 2))

;; 3.
(define (circle-properties r)
  (list (area-circle r) r)
  )


;; 4.
(define (rectangle-properties x y)
  (list (* x y) (+ x x y y))
  )

;; 5.
(define (find-needle ls)
  (string-contains "hay needle hay" "needle")
  )
#|
;; 6.
(define (abs x)
  )

;; 7.
(define (inclis1 ls)
  )

;; 8.
(define (even? x)
  )

;; 9.
(define another-add
  (lambda (n m)
    ))

(provide (all-defined-out))
|#
