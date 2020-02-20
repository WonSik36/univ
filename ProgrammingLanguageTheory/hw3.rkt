#lang plai

; Programming Language Theory 02
; HW3 Understanding Substitution
; 21300691 WonSik Cheung

; solve by myself
; 2hour 30 minutes

;<WAE> ::= <num>
;         | {+ <WAE> <WAE>}
;         | {- <WAE> <WAE>}
;         | {with {<id> <WAE>} <WAE>}
;         | <id>

(define-type WAE
	[num (n number?)]
	[add (lhs WAE?) (rhs WAE?)]
	[sub (lhs WAE?) (rhs WAE?)]
	[with (name symbol?) (named-expr WAE?) (body WAE?)]
	[id (name symbol?)])





;[contract]: symbol1 symbol2 → boolean
;[purpose]: take 2 symbol and return true when first symbol is preceded by second symbol. If not than return false.
(define (symbol<? a b) (string<? (symbol->string a) (symbol->string b)))

;;[test]: symbol<?
(test (symbol<? 'abc 'adf) #t)
(test (symbol<? 'f 'a) #f)
(test (symbol<? 'qwerty '12f) #f)
(test (symbol<? 'hello 'world) #t)

;[contract]: list-of-sym → list-of-sym
;[purpose]: takes a list of symbol and produces a list of symbols which is ordered
(define (sort-list lst)
  (sort lst symbol<?))

;;[test]: sort-list
(test (sort-list '(c b a)) '(a b c))
(test (sort-list '(c b a x y)) '(a b c x y))
(test (sort-list '(c b a x x)) '(a b c x x))
(test (sort-list '(a a a)) '(a a a))

;[contract]: list-of-sym → list-of-sym
;[purpose]: make list ordered and remove repitition
(define (make-list-pretty lst)
  (sort-list (set->list (list->set lst))))

;;[test]: make-list-pretty
(test (make-list-pretty '(c b a)) '(a b c))
(test (make-list-pretty '(c b a a x y)) '(a b c x y))
(test (make-list-pretty '(c b a x x)) '(a b c x))
(test (make-list-pretty '(a a a)) '(a))





; ========= TASK1: implement free-ids =========

;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is free identifier with repitition
(define (free-ids-with-rept wae)
  (type-case WAE wae
    [num (n) (list)]
    [add (l r) (append (free-ids-with-rept l) (free-ids-with-rept r))]
    [sub (l r) (append (free-ids-with-rept l) (free-ids-with-rept r))]
    [with (i v e) (append (free-ids-with-rept v) (remove* (list i) (free-ids-with-rept e)))]
    [id	(s) (list s)]))

;;[test]: free-ids-with-rept
(test (free-ids-with-rept (with 'x (num 3) (sub (id 'a) (sub (id 'b) (add (id 'x) (id 'b)))))) '(a b b)) ;;
(test (free-ids-with-rept (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'b) (id 'a))))))) '(y b a))
(test (free-ids-with-rept (with 'x (id 't) (sub (id 'x) (with 'y (id 'y) (add (id 'x) (sub (id 'b) (id 'a))))))) '(t y b a))
(test (free-ids-with-rept (with 'x (with 'y (num 3) (sub (id 'x) (id 'y))) (add (id 'x) (id 'y)))) '(x y))

;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is free identifier
(define (free-ids wae)
  (make-list-pretty (free-ids-with-rept wae)))

;;[test]: free-ids
(test (free-ids (with 'x (num 3) (add (id 'x) (sub (num 3) (id 'x))))) '())
(test (free-ids (with 'x (num 3) (sub (id 'a) (add (num 4) (id 'x))))) '(a))
(test (free-ids (with 'x (num 3) (sub (id 'b) (sub (id 'a) (id 'x))))) '(a b))
(test (free-ids (with 'x (num 3) (sub (id 'a) (sub (id 'b) (add (id 'x) (id 'b)))))) '(a b))
(test (free-ids (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'b) (id 'a))))))) '(a b y))
(test (free-ids (with 'x (id 't) (sub (id 'x) (with 'y (id 'y) (add (id 'x) (sub (id 'b) (id 'a))))))) '(a b t y))
(test (free-ids (with 'x (with 'y (num 3) (sub (id 'x) (id 'y))) (add (id 'x) (id 'y)))) '(x y))(test (free-ids (add (with 'x (num 10) (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'c) (id 'b))))))) (with 'a (id 'a) (id 'a)))) '(a b c y))
(test (free-ids (add (with 'x (num 10) (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'c) (id 'b))))))) (with 'a (id 'd) (id 'a)))) '(b c d y))
(test (free-ids (add (with 'x (num 10) (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'c) (id 'b))))))) (with 'a (id 'd) (id 'z)))) '(b c d y z))





; ========= TASK2: implement binding-ids =========
;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is binding identifier with repitition
(define (binding-ids-with-rept wae)
  (type-case WAE wae
    [num (n) (list)]
    [add (l r) (append (binding-ids-with-rept l) (binding-ids-with-rept r))]
    [sub (l r) (append (binding-ids-with-rept l) (binding-ids-with-rept r))]
    [with (i v e) (append (binding-ids-with-rept v) (append (list i) (binding-ids-with-rept e)))]
    [id	(s) (list)]))

;;[test]: binding-ids-with-rept
(test (free-ids-with-rept (with 'x (num 3) (sub (id 'a) (sub (id 'b) (add (id 'x) (id 'b)))))) '(a b b)) ;;
(test (free-ids-with-rept (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'b) (id 'a))))))) '(y b a))
(test (free-ids-with-rept (with 'x (id 't) (sub (id 'x) (with 'y (id 'y) (add (id 'x) (sub (id 'b) (id 'a))))))) '(t y b a))
(test (free-ids-with-rept (with 'x (with 'y (num 3) (sub (id 'x) (id 'y))) (add (id 'x) (id 'y)))) '(x y))

;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is binding identifier
(define (binding-ids wae)
  (make-list-pretty (binding-ids-with-rept wae)))

;;[test]: binding-ids
(test (binding-ids (add (num 3) (sub (id 'x) (id 'y)))) '())
(test (binding-ids (with 'y (num 3) (with 'x (id 'x) (id 'y)))) '(x y))
(test (binding-ids (with 'y (num 3) (with 'y (id 'x) (add (id 'x) (id 'y))))) '(y))
(test (binding-ids (with 'y (num 3) (with 'y (with 'x (add (num 3) (id 'y)) (sub (id 'x) (id 'y))) (add (id 'x) (id 'y))))) '(x y))
(test (binding-ids (with 'z (num 3) (with 'w (with 'z (add (num 3) (id 'y)) (sub (id 'x) (id 'y))) (with 'w (id 'y) (add (num 7) (id 'w)))))) '(w z))





; ========= TASK3: implement bound-ids =========
;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is identifier
(define (all-ids wae)
  (type-case WAE wae
    [num (n) (list)]
    [add (l r) (append (all-ids l) (all-ids r))]
    [sub (l r) (append (all-ids l) (all-ids r))]
    [with (i v e) (append (list i) (append (all-ids v) (all-ids e)))]
    [id	(s) (list s)]))

;;[test]: all-ids
(test (all-ids (add (num 3) (sub (id 'x) (id 'y)))) '(x y))
(test (all-ids (with 'y (num 3) (with 'x (id 'x) (id 'y)))) '(y x x y))
(test (all-ids (with 'y (num 3) (with 'y (id 'x) (add (id 'x) (id 'y))))) '(y y x x y))
(test (all-ids (with 'y (num 3) (with 'y (with 'x (add (num 3) (id 'y)) (sub (id 'x) (id 'y))) (add (id 'x) (id 'y))))) '(y y x y x y x y))
(test (all-ids (with 'z (num 3) (with 'w (with 'z (add (num 3) (id 'y)) (sub (id 'x) (id 'y))) (with 'w (id 'y) (add (num 7) (id 'w)))))) '(z w z y x y w y w))

;[contract]: list-of-sym list-of-sym → list-of-sym
;[purpose]: take 2 list and subtract second list from first list
(define (subtList lst1 lst2)
  (cond
    [(= (length lst2) 0) lst1]
    [else (subtList (remove (first lst2) lst1) (rest lst2))]))

;;[test]: subList
(test (subtList (list 'a 'b 'c) (list 'a)) (list 'b 'c))
(test (subtList (list 'a 'b 'c 'd 'a) (list 'a 'b)) (list 'c 'd 'a))
(test (subtList (list 'a 'b 'c 'c) (list 'a 'c 'c)) (list 'b))
(test (subtList (list 'a 'b 'c) (list )) (list 'a 'b 'c))

;[contract]: WAE → list-of-sym
;[purpose]: takes a WAE and produces a list of symbols which is bound identifier
;implement it by subtract free idtf and binding idtf from all idtf
(define (bound-ids wae)
  (make-list-pretty(subtList (subtList (all-ids wae) (binding-ids-with-rept wae)) (free-ids-with-rept wae))))

;;[test]: bound-ids
(test (bound-ids (with 'x (num 3) (add (id 'y) (num 3)))) '())
(test (bound-ids (with 'x (num 3) (add (id 'x) (sub (id 'x) (id 'y))))) '(x))
(test (bound-ids (with 'x (num 3) (add (id 'x) (with 'y (num 7) (sub (id 'x) (id 'y)))))) '(x y))
(test (bound-ids (with 'x (num 3) (with 'y (id 'x) (sub (num 3) (id 'y))))) '(x y))
(test (bound-ids (with 'x (num 3) (add (id 'y) (with 'y (id 'x) (sub (num 3) (num 7)))))) '(x))
(test (bound-ids (with 'x (id 'x) (add (id 'y) (with 'y (id 'y) (sub (num 3) (with 'z (num 7) (sub (id 'z) (id 'x)))))))) '(x z))
(test (bound-ids (with 'x (with 'y (num 3) (add (id 'x) (id 'y))) (add (id 'y) (with 'y (id 'y) (sub (num 3) (num 7)))))) '(y))
(test (bound-ids (with 'x (id 'a) (with 'y (id 'b) (with 'z (id 'c) (add (id 'd) (sub (id 'x) (add (id 'y) (id 'z)))))))) '(x y z))
(test (bound-ids (add (with 'x (num 10) (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'c) (id 'b))))))) (with 'a (id 'd) (id 'a)))) '(a x))
(test (bound-ids (add (with 'x (num 10) (with 'x (num 3) (sub (id 'y) (with 'y (num 7) (add (id 'x) (sub (id 'c) (id 'b))))))) (with 'a (id 'd) (id 'z)))) '(x))
