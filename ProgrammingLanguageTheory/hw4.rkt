#lang plai

; Programming Language Theory 02
; HW4 Understanding Laziness and Recursion
; 21300691 WonSik Cheung

; solve by myself
; 1hour 30 minutes

;********************************************* Concrete Syntax ******************************************

;<RCFAE> ::= <num>
;          | {+ <RCFAE> <RCFAE>}
;          | {- <RCFAE> <RCFAE>}
;          | {* <RCFAE> <RCFAE>}
;          | <id>
;          | {fun {<id} <RCFAE>}
;          | {<RCFAE> <RCFAE>}
;          | {if0 <RCFAE> <RCFAE> RCFAE>}
;          | {rec {<id> <RCFAE>} <RCFAE>}

;********************************************* Abstract Syntax ******************************************

(define-type RCFAE
    [num (n number?)]
    [add (lhs RCFAE?) (rhs RCFAE?)]
    [sub (lhs RCFAE?) (rhs RCFAE?)]
    [mult (lhs RCFAE?) (rhs RCFAE?)]
    [id (name symbol?)]
    [fun (param symbol?) (body RCFAE?)]
    [app (fun-expr RCFAE?) (arg-expr RCFAE?)]
    [if0 (test-expr RCFAE?) (then-expr RCFAE?) (else-expr RCFAE?)]
    [rec (name symbol?) (named-expr RCFAE?) (fst-call RCFAE?)])

(define-type DefrdSub
    [mtSub]
    [aSub (name symbol?)(value RCFAE-Value?)(ds DefrdSub?)]
    [aRecSub  (name symbol?)(value-box (box/c RCFAE-Value?))(ds DefrdSub?)]) ; for recursion

(define-type RCFAE-Value
    [numV (n number?)]
    [closureV (param symbol?) (body RCFAE?) (ds DefrdSub?)]
    [exprV (expr RCFAE?) (ds DefrdSub?) (value (box/c (or/c false RCFAE-Value?)))]) ; for laziness

;[contract]: sexp → RCFAE
;[purpose]: parse sexp to RCFAE
(define (parse sexp)
   (match sexp
        [(? number?) (num sexp)]
        [(list '+ l r) (add (parse l) (parse r))]
        [(list '- l r) (sub (parse l) (parse r))]
        [(list '* l r) (mult (parse l) (parse r))]
        [(list 'with (list i v) e) (app (fun i (parse e)) (parse v))]  ;; with is deprecated but I'll use it
        [(? symbol?) (id sexp)]
        [(list 'fun (list p) b) (fun p (parse b))]  ;; e.g., {fun {x} {+ x 1}}
        [(list f a) (app (parse f) (parse a))]
        [(list 'if0 test then else) (if0 (parse test)(parse then)(parse else))]
        [(list 'rec (list i expr) fst) (rec i (parse expr)(parse fst))]
        [else (error 'parse "bad syntax: ~a" sexp)]))

;[contract]: RCFAE-Value → boolean
;[purpose]: check RCFAE-Value(numV) is 0
(define (numzero? n)
    (zero? (numV-n n)))

;[contract]: RCFAE-Value RCFAE-Value -> RCFAE-Value
;[purpose]: calculate two RCFAE-Value with given operator
(define (num-op op)
     (lambda (x y)
          (numV (op (numV-n (strict x)) (numV-n (strict y))))))

;[contract]: RCFAE-Value RCFAE-Value -> RCFAE-Value
;[purpose]: add RCFAE-Value to RCFAE-Value
(define num+ (num-op +))

;[contract]: RCFAE-Value RCFAE-Value -> RCFAE-Value
;[purpose]: subtract RCFAE-Value to RCFAE-Value
(define num- (num-op -))

;[contract]: RCFAE-Value RCFAE-Value -> RCFAE-Value
;[purpose]: multiply RCFAE-Value to RCFAE-Value
(define num* (num-op *))

;[contract]: LFAE-Value(exprV) -> LFAE-Value(Not exprV)
;[purpose]: calculate exprV if it is not cached
(define (strict v)
    (type-case RCFAE-Value v
        [exprV (expr ds v-box) (if (not (unbox v-box))    ;; box contains #f? Then evaluate expr as needed.
                          (local [(define v (strict (interp expr ds)))] 
                            (begin (set-box! v-box v) v))      ;; return v after evaluating it.
                          (unbox v-box))] ;; if box contain numV or closureV than return it
        [else v]))

;[contract]: symbol DefrdSub -> RCFAE-Value
;[purpose]: get cached value from defered sub
(define (lookup name ds)
    (type-case DefrdSub ds
        [mtSub  () (error 'lookup "free variable")]
        [aSub    (sub-name val rest-ds)
                 (if (symbol=? sub-name name)
                     val (lookup name rest-ds))]
        [aRecSub (sub-name val-box rest-ds)
                 (if (symbol=? sub-name name)
                     (unbox val-box) (lookup name rest-ds))]))

;[contract]: RCFAE DefrdSub -> RCFAE-Value
;[purpose]: interpret RCFAE to RCFAE-Value by using defered sub
(define (interp rcfae ds)
    (type-case RCFAE rcfae
        [num (n) (numV n)]
        [add  (l r) (num+ (interp l ds) (interp r ds))]
        [sub  (l r) (num- (interp l ds) (interp r ds))]
        [mult  (l r) (num* (interp l ds) (interp r ds))]
        [id     (name) (strict (lookup name ds))]
        [fun   (param body-expr) (closureV param body-expr ds)]
        [app  (f a) (local [(define f-val (strict (interp f ds)))
                            (define a-val (exprV a ds (box #f)))]
                      (interp (closureV-body f-val) (aSub (closureV-param f-val) a-val (closureV-ds f-val))))]     
        [if0   (test-expr then-expr else-expr) 
              (if (numzero? (interp test-expr ds))(interp then-expr ds)(interp else-expr ds))]
        [rec  (bound-id func-expr fst-call)
                 (local [(define value-holder (box (numV 198)))
                         (define new-ds (aRecSub bound-id value-holder ds))]
                         (begin (set-box! value-holder (interp func-expr new-ds))
                                (interp fst-call new-ds)))]))

;[contract]: sexp -> RCFAE-Value
;[purpose]: parse sexp to RCFAE and interpret RCFAE to RCFAE-Value
(define (run sexp)
     (interp (parse sexp) (mtSub)))


;;******************************************************************** TEST ********************************************************;

;; test for FAE
(test (run '{+ 1 {- 2 3}}) (numV 0))
(test/exn (run '{- 5 {+ 1 2 3}}) "parse: bad syntax: (+ 1 2 3)")
(test (run '{with {x 5} {+ x x}}) (numV 10))
(test (run '{with {x 3} {with {f {fun {y} {+ x y}}} {with {x 5} {f 4}}}}) (numV 7))


;; test for recursion
(test(run '{rec {fac {fun {n}
                     {if0 n
                          1
                          {* n {fac {- n 1}}}}}}
        {fac 10}}) (numV 3628800))

(test(run '{rec {fibo {fun {n}
                     {if0 {- n 1}
                          1
                          {if0 {- n 2}
                              1
                              {+ {fibo {- n 1}} {fibo {- n 2}}}}}}}
        {fibo 10}}) (numV 55))

(test(run '{rec {sum {fun {n}
                     {if0 n
                          0
                          {+ n {sum {- n 1}}}}}}
        {sum 10}}) (numV 55))

;; test for Laziness
(test (run '{{fun {x} 0} {+ 1 {fun {y} 2}}}) (numV 0))
;(test/exn (run '{{fun {x} x} {+ 1 {fun {y} 2}}}) "contract violation")
(test (run  '{rec {fac {fun {n}
                     {if0 n
                          {{fun {x} 1} {+ 1 {fun {y} 2}}}
                          {* n {fac {- n 1}}}}}}
        {fac 10}})(numV 3628800))
(test(run '{rec {sum {fun {n}
                     {if0 n
                          0
                          {+ n {sum {- n 1}}}}}}
        {sum {{fun {x} 10} {+ 1 {fun {y} 2}}}}}) (numV 55))
(test (run '{{fun {x} 0} {rec {fac {fun {n}
                     {if0 n
                          {{fun {x} 1} {+ 1 {fun {y} 2}}}
                          {* n {fac {- n 1}}}}}}
        {fac 10}}}) (numV 0))

(test (run '{rec {triangle {fun {rows} {if0 rows 0 {+ rows {triangle {- rows 1}}}}}} {triangle 7}}) (numV 28))
(test (interp (parse '{rec {bunnyEars {fun {bunnies} {if0 bunnies 0 {+ ears {bunnyEars {- bunnies 1}}}}}} {bunnyEars 234}}) (aSub 'ears (numV 2) (mtSub))) (numV 468))
(test (run '{{fun {x} {if0 {- x 198} x {+ x x}}} {{fun {y} {with {z 3} {{fun {s} {+ {+ s z} y}} 0}}} 1}}) (numV 8))
(test (run '{{fun {x} x} {fun {y} {with {z 3} {{fun {s} s} 0}}}}) (closureV 'y (app (fun 'z (app (fun 's (id 's)) (num 0))) (num 3)) (mtSub)))
(test (run '{rec {fibonacci {fun {n} {if0 n 1 {if0 {+ n 1} 1 {+ {fibonacci {- n 2}} {fibonacci {- n 1}}}}}}} {fibonacci 10}}) (numV 144))
(test (run '{{fun {x} {- {+ {- {+ x x} {+ x x}} x} {+ x {- {+ x x} {+ x x}}}}} {- {+ 1 {- {+ 4 5} {+ 8 1}}} {+ 2 {- {+ 4 5} {+ 8 7}}}}}) (numV 0))
(test (run '{{fun {x} x} {+ 5 5}}) (numV 10))
(test (run '{{fun {x} 0} {+ {fun {z} 3} {fun {y} {fun {o} 2}}}}) (numV 0))
(test (run '{{fun {x} {+ 3 5}} {+ {fun {z} 3} {fun {y} {fun {o} 2}}}}) (numV 8))
(run '{{fun {x} x} {+ {fun {x} x} 5}})