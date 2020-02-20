#lang plai

; Programming Language Theory 02
; 21300691 WonSik Cheung
; This is another language, ArithC, that supports only addition (plusC) and multiplication (multC).
; Example code of this language is as follows
; {+ 1 {+ 2 3}}
; {* 3 {* 2 {+ 3 4}}}

; BNF for ArithC
; <ArithC> := <numC>
;             | {+ <ArithC> <ArithC>}
;             | {* <ArithC> <ArithC>}
; 
; Assume we know terminals as follows:
; <numC> can be replaced wtih any numbers.

; Data type for ArithC
(define-type ArithC
  [numC (n number?)]
  [plusC (l ArithC?) (r ArithC?)]
  [multC (l ArithC?) (r ArithC?)])

; ========= TASK1: write [contract] and [purpose] for all functions. Check sub tasks, TASK1-1, 1-2, 1-3, and 1-4.

; ===TASK1-1
;[contract]: s-expression which has number, plus and multiply operation -> ArithC
;[purpose]: To parse s-expression and convert it to ArithC
(define (parse s)
  (cond
    [(number? s) (numC s)]
    [(eq? (first s) '+) (plusC (parse (second s)) (parse (third s)))]
    [(eq? (first s) '*) (multC (parse (second s)) (parse (third s)))]
    [else (error 'parse "bad syntax: ~a" s)]))


; BNF for ArithS which supports binary subtration as well
; <ArithS> := <numC>
;             | {+ <ArithS> <ArithS>}
;             | {* <ArithS> <ArithS>}
;             | {- <ArithS> <ArithS>}
; 
; Asuume we know terminals as follows:
; <numC> is any numbers.

; Data type for ArithC
(define-type ArithS
  [numS (n number?)]
  [plusS (l ArithS?) (r ArithS?)]
  [multS (l ArithS?) (r ArithS?)]
  [bminusS (l ArithS?) (r ArithS?)])

; ===TASK1-2
;[contract]: s-expression which has number, plus, multiply and minus operation -> ArithS
;[purpose]: To parse s-expression and convert it to ArithS
(define (parseForArithS s)
  (cond
    [(number? s) (numS s)]
    [(eq? (first s) '+) (plusS (parseForArithS (second s)) (parseForArithS (third s)))]
    [(eq? (first s) '*) (multS (parseForArithS (second s)) (parseForArithS (third s)))]
    [(eq? (first s) '-) (bminusS (parseForArithS (second s)) (parseForArithS (third s)))]
    [else (error 'parse "bad syntax: ~a" s)]))


; ===TASK1-3
;[contract]: ArithS -> ArithC
;[purpose]: To convert ArithS to ArithC
; ===TASK2: Implement desugar function. Check this link for your reference. http://cs.brown.edu/courses/cs173/2012/book/first-desugar.html
; If you can successfully implement this, the last three test cases will pass!!
(define (desugar as)
  (type-case ArithS as
    [numS (n) (numC n)]
    [plusS (l r) (plusC (desugar l)
                        (desugar r))]
    [multS (l r) (multC (desugar l)
                        (desugar r))]
    [bminusS (l r) (plusC (desugar l)
                        (multC (numC -1) (desugar r)))]))

; ===TASK1-4
;[contract]: ArithC -> number
;[purpose]: To calculate ArithC and get result from it
(define (interp a)
  (type-case ArithC a
    [numC (n) n]
    [plusC (l r) (+ (interp l) (interp r))]
    [multC (l r) (* (interp l) (interp r))]))

;[tests] for ArithC
(test (interp (parse '{+ 1 {+ 2 3}})) 6)
(test (interp (parse '{* 3 {* 2 {+ 3 4}}})) 42)
(test/exn (interp (parse '{- 1 2})) "parse: bad syntax: (- 1 2)")


;[tests] for ArithS
(test (interp (desugar (parseForArithS '{+ 1 {+ 2 3}}))) 6)
(test (interp (desugar (parseForArithS '{* 3 {* 2 {+ 3 4}}}))) 42)
(test (interp (desugar (parseForArithS '{- 1 2}))) -1)


; TASK3: Asnwer the following questions
; (1) What is syntactic sugar? Explain based on your implementaion.
;  Syntactic sugar is easier syntax to type or read code. For example, if I use ArithC and want to calculate minus operations,
; then I have to convert positive operand to negative, negative operand to positive. But when I use ArithS, it is easy to implement minus operation.
; So ArithS is Syntactic sugar that give clients to easier way of type or read code.
;
; (2) What is desugaring? Explain based on your implementaion. Hint: NOTE THAT WE DO NOT NEED TO CHANGE CURRENT interp implmentation for HW2 **
;  Desugaring is converting syntactic sugar to basic syntax. By desugaring, it doens't need to implement another compiler/interpreter.
; For example, in test for ArithS, parseForArithS convert s-expression to ArithS and desugar convert ArithS to ArithC.
; Therefore the code can use interp, not implement interpreter for ArithS.
