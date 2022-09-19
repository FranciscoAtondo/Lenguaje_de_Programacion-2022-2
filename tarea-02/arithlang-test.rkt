#lang plait

(define-type ArithC
	(NumberC [num : Number])
	(plusC    [firstSC : ArithC]
			 [second : ArithC]) 
	(multC   [firstMC : ArithC]
			 [second : ArithC]))

(define-type ArithS
	(NumberS [num : Number])
	(plusS    [firstSS : ArithS]
			 [secondSS : ArithS])
	(multS   [firstMS : ArithS]
			 [secondMS : ArithS])
	(restS   [firstRS : ArithS]
			 [secondRS : ArithS])
	(negS    [numS : ArithS]))

(define (eval [input : S-Exp]) : Number
  (interp (desugar (parse input))))

(define (interp [expC : ArithC]) : Number
  (cond
	[(NumberC? expC) (NumberC-num expC)]
	[(sumC? expC) (+ (interp (plusC-firstSC expC)) (interp (plusC-second expC)))]
	[(multC? expC) (* (interp (multC-firstMC expC)) (interp (multC-secondMC expC)))]))

(define (parse [s : S-Exp]) : ArithC
  (cond [(s-exp-number? s) (numC (s-exp->number s))]
    [(s-exp-list? s)
      (let ([ls (s-exp->list s)])
        (case (s-exp->symbol (first ls))
          [(+) (plusC (parse (second ls)) (parse (third ls)))]
          [(*) (multC (parse (second ls)) (parse (third ls)))]
          [else (error 'parse ”operación aritmética malformada”)]))]
    [else (error 'parse ”expresión aritmética malformada”)]))

(define (unit-string? x)
  (and (string? x)
       (= (string-length x) 1)))

(define (unit-string-list? x)
  (or (null? x)
      (and (pair? x)
           (string? (first x))
           (= (string-length (first x)) 1)
           (unit-string-list? (rest x)))))
