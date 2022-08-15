#lang racket

(define pi 3.14)
(define (areaCirc x y)
  (-> integer? integer? integer?)
  (* x (pow y)))

(define (pow y)
  (-> integer?)
  (expt y 2))
