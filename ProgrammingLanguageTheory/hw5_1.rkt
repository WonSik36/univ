#lang plai

; Programming Language Theory 02
; HW5 Understanding Variables(Task 1)
; 21300691 WonSik Cheung

; solve by myself
; 20 minutes

;********************************************* Concrete Syntax ******************************************
; RBMFAE = BFAE + Variables + Call-by-Reference
;<RBMFAE> ::= <num>
;         | {+ <RBMFAE> <RBMFAE>}
;         | {- <RBMFAE> <RBMFAE>}
;         | <id>
;         | {fun {<id>} <RBMFAE>}
;         | {refun {<id>} <RBMFAE>}
;         | {<RBMFAE> <RBMFAE>}
;         | {newbox <RBMFAE>} ;define/initalize box
;         | {setbox <RBMFAE> <RBMFAE>} ;update a box
;         | {openbox <RBMFAE>}  ;;extract value from a box
;         | {seqn <RBMFAE> <RBMFAE>} ;; run two expression sequentially
;         | {setvar <id> <RBMFAE>}


;********************************************* Abstract Syntax ******************************************
(define-type RBMFAE
    [num (n number?)]
    [add (lhs RBMFAE?) (rhs RBMFAE?)]
    [sub (lhs RBMFAE?) (rhs RBMFAE?)]
    [id (name symbol?)]
    [refun (param symbol?) (body RBMFAE?)]
    [fun (param symbol?) (body RBMFAE?)]
    [app (fun-expr RBMFAE?) (arg-expr RBMFAE?)]
    [newbox  (v RBMFAE?)]
    [setbox  (bn RBMFAE?) (v RBMFAE?)]
    [openbox  (v RBMFAE?)]
    [seqn  (ex1 RBMFAE?) (ex2 RBMFAE?)]
    [setvar (id symbol?) (val-expr RBMFAE?)])

(define-type DefrdSub
    [mtSub]
    [aSub (name symbol?)(address integer?)(ds DefrdSub?)])

(define-type Store
            [mtSto]
            [aSto  (address integer?) (value RBMFAE-Value?) (rest Store?)])

(define-type RBMFAE-Value
    [numV (n number?)]
    [closureV (param symbol?) (body RBMFAE?) (ds DefrdSub?)]
    [refclosV (param symbol?) (body RBMFAE?) (ds DefrdSub?)]
    [boxV (address integer?)])

(define-type Value*Store
  [v*s (value RBMFAE-Value?) (store Store?)])

;[contract]: sexp → RBMFAE
;[purpose]: parse sexp to RBMFAE
(define (parse sexp)
   (match sexp
        [(? number?) (num sexp)]
        [(list '+ l r) (add (parse l) (parse r))]
        [(list '- l r) (sub (parse l) (parse r))]
        [(list 'with (list i v) e) (app (fun i (parse e)) (parse v))]  ;; with is deprecated but I'll use it
        [(? symbol?) (id sexp)]
        [(list 'fun (list p) b) (fun p (parse b))]  ;; e.g., {fun {x} {+ x 1}}
        [(list 'refun (list p) b) (refun p (parse b))]
        [(list 'newbox v) (newbox (parse v))]
        [(list 'setbox i v) (setbox (parse i) (parse v))]
        [(list 'openbox i) (openbox (parse i))]
        [(list 'seqn e1 e2) (seqn (parse e1) (parse e2))]
        [(list 'setvar i v) (setvar i (parse v))]
        [(list f a) (app (parse f) (parse a))] ;; app
        [else (error 'parse "bad syntax: ~a" sexp)]))

;[contract]: RBMFAE-Value RBMFAE-Value -> RBMFAE-Value
;[purpose]: calculate two RBMFAE-Value with given operator
(define (num-op op)
     (lambda (x y)
          (numV (op (numV-n x) (numV-n y)))))

;[contract]: RBMFAE-Value RBMFAE-Value -> RBMFAE-Value
;[purpose]: add RBMFAE-Value to RBMFAE-Value
(define num+ (num-op +))

;[contract]: RBMFAE-Value RBMFAE-Value -> RBMFAE-Value
;[purpose]: subtract RBMFAE-Value to RBMFAE-Value
(define num- (num-op -))

;[contract]: symbol DefrdSub -> address
;[purpose]: get address from defered sub
(define (lookup name ds)
    (type-case DefrdSub ds
        [mtSub  () (error 'lookup "free variable")]
        [aSub    (i adr rest)
                 (if (symbol=? i name)
                     adr (lookup name rest))]))

;[contract]: address Store -> RBMFAE-Value
;[purpose]: get RBMFAE value from Store by using address
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


;[contract]: RBMFAE DefrdSub Store -> Value*Store
;[purpose]: interpret RBMFAE to RBMFAE-Value by using defered sub
(define (interp rbmfae ds st)
    (type-case RBMFAE rbmfae
        [num (n) (v*s (numV n) st)]
        [add  (l r) (interp-two l r ds st (lambda (v1 v2 st1) (v*s (num+ v1 v2) st1)))]
        [sub  (l r) (interp-two l r ds st (lambda (v1 v2 st1) (v*s (num- v1 v2) st1)))]
        [id     (name) (v*s (store-lookup (lookup name ds) st) st)]
        [fun   (param body-expr) (v*s (closureV param body-expr ds) st)]
        [refun (param body-expr) (v*s (refclosV param body-expr ds) st)]
        [app (f a) (type-case Value*Store (interp f ds st) [v*s (f-value f-store)
                    (type-case RBMFAE-Value f-value
                            [closureV (c-param c-body c-ds)
                                      (type-case Value*Store (interp a ds f-store) [v*s (a-value a-store)
                                      (local ([define new-address (malloc a-store)])
                                             (interp c-body (aSub c-param new-address c-ds) (aSto new-address a-value a-store)))])]
                            [refclosV (rc-param rc-body rc-ds)(local ([define address (lookup (id-name a) ds)])
                                             (interp rc-body (aSub rc-param address rc-ds) (aSto address (store-lookup address f-store) f-store)))]
                            [else (error interp "trying to apply a number")])])]
        [newbox (v) (type-case Value*Store (interp v ds st) [v*s (vl st1)
                    (local [(define adr (malloc st1))]
                            (v*s (boxV adr) (aSto adr vl st1)))])] ;; new box has address of RBMFAE-Value

        [setbox (bx v) (interp-two bx v ds st (lambda (bx-val val st1) (v*s val (aSto (boxV-address bx-val) val st1))))]
      
        [openbox (bx) (type-case Value*Store (interp bx ds st) [v*s (bx-val st1)
                            (v*s (store-lookup (boxV-address bx-val)st1)st1)])]
        [seqn (e1 e2) (interp-two e1 e2 ds st (lambda (v1 v2 st1) (v*s v2 st1)))]
        [setvar (id val-expr) (local[(define adr (lookup id ds))]
                                (type-case Value*Store (interp val-expr ds st)
                                  [v*s (val st) (v*s val (aSto adr val st))]))]
))
;[contract]: sexp DefrdSub Store -> Value*Store
;[purpose]: parse sexp to RBMFAE and interpret RBMFAE to Value*Store
(define (run sexp ds st)
     (interp (parse sexp) ds st))

;[contract]: sexp -> RBMFAE-Value
;[purpose]: parse sexp to RBMFAE and interpret RBMFAE to RBMFAE-Value
(define (run-value sexp)
     (v*s-value (interp (parse sexp) (mtSub) (mtSto))))


;******************************************************************** TEST ********************************************************

(test (run '{with {a 3} {setvar a 5}} (mtSub) (mtSto)) (v*s (numV 5) (aSto 1 (numV 5) (aSto 1 (numV 3) (mtSto)))))
(test (run '{with {a 3} {seqn {{fun {x} {setvar x 5}} a} a}} (mtSub) (mtSto)) (v*s (numV 3) (aSto 2 (numV 5) (aSto 2 (numV 3) (aSto 1 (numV 3) (mtSto))))))
(test (run-value '{with {swap {fun {x} {fun {y} {with {z x} {seqn {setvar x y}{setvar y z}}}}}}
                  {with {a 10} {with {b 20} {seqn {{swap a} b} a}}}}) (numV 10))
(test(run '{with {swap {refun {x}
                       {refun {y}
                            {with {z x} ;;; z will be processed as call-by-reference.
                                  {seqn {setvar x y}
                                        {setvar y z}}}}}}
            {with {a 10}
                  {with {b 20}
                        {seqn {{swap a} b}
                              a}}}}(mtSub) (mtSto))
     (v*s (numV 20) (aSto 3 (numV 10) (aSto 2 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (refclosV 'x (refun 'y (app (fun 'z (seqn (setvar 'x (id 'y)) (setvar 'y (id 'z)))) (id 'x))) (mtSub)) (mtSto)))))))))))
(test(run '{with {swap {refun {x}
                       {refun {y}
                            {with {z x} ;;; z will be processed as call-by-reference.
                                  {seqn {setvar x y}
                                        {setvar y z}}}}}}
            {with {a 10}
                  {with {b 20}
                        {seqn {{swap a} b}
                              b}}}}(mtSub) (mtSto))
     (v*s (numV 10) (aSto 3 (numV 10) (aSto 2 (numV 20) (aSto 4 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 3 (numV 20) (aSto 2 (numV 10) (aSto 1 (refclosV 'x (refun 'y (app (fun 'z (seqn (setvar 'x (id 'y)) (setvar 'y (id 'z)))) (id 'x))) (mtSub)) (mtSto)))))))))))