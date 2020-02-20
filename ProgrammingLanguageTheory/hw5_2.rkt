#lang plai

; Programming Language Theory 02
; HW5 Understanding Variables(Task 2)
; 21300691 WonSik Cheung

; solve by myself
; 2hours

;********************************************* Concrete Syntax ******************************************
;<BMFAE> ::= <num>
;         | {+ <BMFAE> <BMFAE>}
;         | {- <BMFAE> <BMFAE>}
;         | <id>
;         | {fun <prm> <BMFAE>}
;         | {<BMFAE> <BMFAE>}
;         | {newbox <BMFAE>} ;define/initalize box
;         | {setbox <BMFAE> <BMFAE>} ;update a box
;         | {openbox <BMFAE>}  ;;extract value from a box
;         | {seqn <BMFAE> <BMFAE>} ;; run two expression sequentially
;         | {setvar <id> <BMFAE>}
;
; <id> = any symbol supported by Racket
; <prm>::= {val <id>} | {ref <id>}


;********************************************* Abstract Syntax ******************************************
(define-type BMFAE
    [num (n number?)]
    [add (lhs BMFAE?) (rhs BMFAE?)]
    [sub (lhs BMFAE?) (rhs BMFAE?)]
    [id (name symbol?)]
    [fun (param Prm?) (body BMFAE?)]
    [app (fun-expr BMFAE?) (arg-expr BMFAE?)]
    [newbox  (v BMFAE?)]
    [setbox  (bn BMFAE?) (v BMFAE?)]
    [openbox  (v BMFAE?)]
    [seqn  (ex1 BMFAE?) (ex2 BMFAE?)]
    [setvar (id symbol?) (val-expr BMFAE?)])

(define-type Prm
  [prm (type symbol?) (name symbol?)])

(define-type DefrdSub
    [mtSub]
    [aSub (name symbol?)(address integer?)(ds DefrdSub?)])

(define-type Store
            [mtSto]
            [aSto  (address integer?) (value BMFAE-Value?) (rest Store?)])

(define-type BMFAE-Value
    [numV (n number?)]
    [closureV (type Prm?) (body BMFAE?) (ds DefrdSub?)]
    [boxV (address integer?)])

(define-type Value*Store
  [v*s (value BMFAE-Value?) (store Store?)])

;[contract]: sexp → BMFAE
;[purpose]: parse sexp to BMFAE
(define (parse sexp)
   (match sexp
        [(? number?) (num sexp)]
        [(list '+ l r) (add (parse l) (parse r))]
        [(list '- l r) (sub (parse l) (parse r))]
        [(list 'with (list i v) e) (app (fun (prm 'val i) (parse e)) (parse v))]  ;; with is deprecated but I'll use it
        [(? symbol?) (id sexp)]
        [(list 'fun (list t p) b) (fun (prm t p) (parse b))]
        [(list 'newbox v) (newbox (parse v))]
        [(list 'setbox i v) (setbox (parse i) (parse v))]
        [(list 'openbox i) (openbox (parse i))]
        [(list 'seqn e1 e2) (seqn (parse e1) (parse e2))]
        [(list 'setvar i v) (setvar i (parse v))]
        [(list f a) (app (parse f) (parse a))] ;; app
        [else (error 'parse "bad syntax: ~a" sexp)]))

;[contract]: BMFAE-Value BMFAE-Value -> BMFAE-Value
;[purpose]: calculate two BMFAE-Value with given operator
(define (num-op op)
     (lambda (x y)
          (numV (op (numV-n x) (numV-n y)))))

;[contract]: BMFAE-Value BMFAE-Value -> BMFAE-Value
;[purpose]: add BMFAE-Value to BMFAE-Value
(define num+ (num-op +))

;[contract]: BMFAE-Value BMFAE-Value -> BMFAE-Value
;[purpose]: subtract BMFAE-Value to BMFAE-Value
(define num- (num-op -))

;[contract]: symbol DefrdSub -> address
;[purpose]: get address from defered sub
(define (lookup name ds)
    (type-case DefrdSub ds
        [mtSub  () (error 'lookup "free variable")]
        [aSub    (i adr rest)
                 (if (symbol=? i name)
                     adr (lookup name rest))]))

;[contract]: address Store -> BMFAE-Value
;[purpose]: get BMFAE value from Store by using address
(define (store-lookup address st)
    (type-case Store st
        [mtSto  () (error 'store-lookup "No value at address")]
        [aSto    (adr v rest)
                 (if (= adr address)
                     v (store-lookup address rest))]))

;[contract]: Store -> Integer
;[purpose]: get address which is maximum address +1 (maximum address is from store)
(define (malloc st)
    (+ 1 (max-address st)))

;[contract]: Store -> Integer
;[purpose]: get address which has maximum address in store
(define (max-address st)
    (type-case Store st
        [mtSto () 0]
        [aSto (n v st)
                  (max n (max-address st))])) ;; check all address in Store

;[contract]: expr1 expr2 DefrdSub Store handle -> Value*Store
;[purpose]: Handle two expression (for sugaring)
(define (interp-two expr1 expr2 ds st handle)
    (type-case Value*Store (interp expr1 ds st)
        [v*s (val1 st2)
    (type-case Value*Store (interp expr2 ds st2)
        [v*s (val2 st3)  ;; st3 has value of va1 and val2
             (handle val1 val2 st3)])]))


;[contract]: BMFAE DefrdSub Store -> Value*Store
;[purpose]: interpret BMFAE to BMFAE-Value by using defered sub
(define (interp bmfae ds st)
    (type-case BMFAE bmfae
        [num (n) (v*s (numV n) st)]
        [add  (l r) (interp-two l r ds st (lambda (v1 v2 st1) (v*s (num+ v1 v2) st1)))]
        [sub  (l r) (interp-two l r ds st (lambda (v1 v2 st1) (v*s (num- v1 v2) st1)))]
        [id     (name) (v*s (store-lookup (lookup name ds) st) st)]
        [fun   (param body-expr) (v*s (closureV param body-expr ds) st)]
        [app (f a) (type-case Value*Store (interp f ds st) [v*s (f-value f-store)
                   (cond
                   [(symbol=? (prm-type(closureV-type f-value)) 'val)
                         (type-case Value*Store (interp a ds f-store) [v*s (a-value a-store) ;; a-store has value of a and f
                         (local ([define new-address (malloc a-store)]) ;; get new address for a-value which has max-address+1 (max-address from a-store)
                                (interp (closureV-body f-value)
                                        (aSub (prm-name (closureV-type f-value)) new-address (closureV-ds f-value))
                                        (aSto new-address a-value a-store)))])]
                   [(symbol=? (prm-type(closureV-type f-value)) 'ref)
                         (local ([define address (lookup(id-name a) ds)]) ;; get address for a-value which already exist in store
                                (interp (closureV-body f-value)
                                        (aSub (prm-name (closureV-type f-value)) address (closureV-ds f-value))
                                        (aSto address (store-lookup address f-store) f-store)))]
                   [else (error interp "other type error")])])]
        [newbox (v) (type-case Value*Store (interp v ds st) [v*s (vl st1)
                    (local [(define adr (malloc st1))]
                            (v*s (boxV adr) (aSto adr vl st1)))])] ;; new box has address of BMFAE-Value

        [setbox (bx v) (interp-two bx v ds st (lambda (bx-val val st1) (v*s val (aSto (boxV-address bx-val) val st1))))]
      
        [openbox (bx) (type-case Value*Store (interp bx ds st) [v*s (bx-val st1)
                            (v*s (store-lookup (boxV-address bx-val)st1)st1)])]
        [seqn (e1 e2) (interp-two e1 e2 ds st (lambda (v1 v2 st1) (v*s v2 st1)))]
        [setvar (id val-expr) (local[(define adr (lookup id ds))]
                                (type-case Value*Store (interp val-expr ds st)
                                  [v*s (val st) (v*s val (aSto adr val st))]))]
))

;[contract]: sexp DefrdSub Store -> Value*Store
;[purpose]: parse sexp to BMFAE and interpret BMFAE to Value*Store
(define (run sexp ds st)
     (interp (parse sexp) ds st))

;[contract]: sexp -> BMFAE-Value
;[purpose]: parse sexp to BMFAE and interpret BMFAE to BMFAE-Value
(define (run-value sexp)
     (v*s-value (interp (parse sexp) (mtSub) (mtSto))))


;******************************************************************** TEST ********************************************************

(test (parse '{{fun {val a} a} 10}) (app (fun (prm 'val 'a) (id 'a)) (num 10)))
(test (parse '{fun {ref a} a}) (fun (prm 'ref 'a) (id 'a)))
(test (parse '{with {x 10} {{fun {ref a} a} x}}) (app (fun (prm 'val 'x) (app (fun (prm 'ref 'a) (id 'a)) (id 'x))) (num 10)))
(test (parse '{with {x 5} x}) (app (fun (prm 'val 'x) (id 'x)) (num 5)))
(test (parse '{with {a 3} {seqn {{fun {val x} {setvar x 5}} a} a}}) (app (fun (prm 'val 'a) (seqn (app (fun (prm 'val 'x) (setvar 'x (num 5))) (id 'a)) (id 'a))) (num 3)))
(test (parse '{with {a 3} {seqn {{fun {ref x} {setvar x 5}} a} a}}) (app (fun (prm 'val 'a) (seqn (app (fun (prm 'ref 'x) (setvar 'x (num 5))) (id 'a)) (id 'a))) (num 3)))

(test (run '{{fun {val a} a} 10} (mtSub) (mtSto)) (v*s (numV 10) (aSto 1 (numV 10) (mtSto))))
(test (run '{fun {ref a} a} (mtSub) (mtSto)) (v*s (closureV (prm 'ref 'a) (id 'a) (mtSub)) (mtSto)))
(test (run '{with {x 10} {{fun {ref a} a} x}} (mtSub) (mtSto)) (v*s (numV 10) (aSto 1 (numV 10) (aSto 1 (numV 10) (mtSto)))))
(test (run '{with {x 5} x} (mtSub) (mtSto)) (v*s (numV 5) (aSto 1 (numV 5) (mtSto))))
(test (run '{with {a 3} {seqn {{fun {val x} {setvar x 5}} a} a}}(mtSub) (mtSto)) (v*s (numV 3) (aSto 2 (numV 5) (aSto 2 (numV 3) (aSto 1 (numV 3) (mtSto))))))
(test (run '{with {a 3} {seqn {{fun {ref x} {setvar x 5}} a} a}}(mtSub) (mtSto)) (v*s (numV 5) (aSto 1 (numV 5) (aSto 1 (numV 3) (aSto 1 (numV 3) (mtSto))))))

(test (run '{with {swap {fun {ref x}
                       {fun {ref y}
                            {with {z x}
                                  {seqn {setvar x y}
                                        {setvar y z}}}}}}
            {with {a 10}
                  {with {b 20}
                        {seqn {{swap a} b}
                              a}}}} (mtSub) (mtSto))

      (v*s (numV 20) (aSto 3 (numV 10) (aSto 2 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (closureV (prm 'ref 'x) (fun (prm 'ref 'y) (app (fun (prm 'val 'z) (seqn (setvar 'x (id 'y)) (setvar 'y (id 'z)))) (id 'x))) (mtSub)) (mtSto)))))))))))

(test (run '{with {swap {fun {ref x}
                       {fun {ref y}
                            {with {z x} ;;; z will be processed as call-by-reference.
                                  {seqn {setvar x y}
                                        {setvar y z}}}}}}
            {with {a 10}
                  {with {b 20}
                        {seqn {{swap a} b}
                              b}}}} (mtSub) (mtSto))
      (v*s (numV 10) (aSto 3 (numV 10) (aSto 2 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (closureV (prm 'ref 'x) (fun (prm 'ref 'y) (app (fun (prm 'val 'z) (seqn (setvar 'x (id 'y)) (setvar 'y (id 'z)))) (id 'x))) (mtSub)) (mtSto)))))))))))

;;contract violation
;;(test (run '{{fun {ref a} a} 10} (mtSub) (mtSto)) (v*s (numV 10) (aSto 1 (numV 10) (mtSto))))