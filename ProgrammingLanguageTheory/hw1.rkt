#lang plai
;Programming Language Theory 02
;21300691 WonSik Cheung
;problem 1***************************************************
;solved by myself: Y
;time taken: 5min
;[contract]dollar->won: number->number
;[purpose] To convert dollar to won
;[test] (test (dollar->won 3) 3600)
;       (test (dollar->won 100) 120000)
(define (dollar->won money)
  (* 1200 money))

(test (dollar->won 3) 3600)
(test (dollar->won 100) 120000)

;problem 2***************************************************
;solved by myself: Y
;time taken: 5min
;[contract]3 numbers->sum: number->number
;[purpose] To sum 3 number
;[test] (test (digit_sum 1 2 3) 6)
;       (test (digit_sum 100 300 500) 900)

(define (digit_sum a b c)
  (+(+ a b)c))

(test (digit_sum 1 2 3) 6)
(test (digit_sum 100 300 500) 900)

;problem 3***************************************************
;solved by myself: Y
;time taken: 5min
;[contract]radius->volume of sphere: number->number
;[purpose] To calculate volume of sphere when radius was given
;[test] (test (volume-spehre 1) 4.187)
;       (test (volume-spehre 5) 523.334)

(define pi 3.14)
(define (volume-spehre a)
  (/(*(*(*(* a a)a)pi)4)3))

(test (volume-spehre 1) 4.187)
(test (volume-spehre 5) 523.334)

;problem 4***************************************************
;solved by myself: Y
;time taken: 5min
;[contract]number->whether is even or odd: number->boolean
;[purpose] To check given number is even or odd
;[test] (test (is-even 8) #t)
;       (test (is-even 9) #f)
(define (is-even a)
  (=(modulo a 2)0))

(test (is-even 8) #t)
(test (is-even 9) #f)

;problem 5***************************************************
;solved by myself: Y
;time taken: 15min

;[contract]number->factorial: number->number
;[purpose] To calcaulate factorial of given number
;[test] (test (factorial 3) 6)
;       (test (factorial 5) 120)
(define (factorial a)
  (cond
    [(= a 0) 1]
    [else (* a (factorial (- a 1)))]))

(test (factorial 3) 6)
(test (factorial 5) 120)

;[contract]2numbers-> combination: number->number
;[purpose] To calcaulate conbination of given number
;[test] (test (combination 3 1) 3)
;       (test (combination 6 2) 15)
(define (combination n k)
  (/(/ (factorial n) (factorial k))(factorial (- n k))))

(test (combination 3 1) 3)
(test (combination 6 2) 15)

;problem 6***************************************************
;solved by myself: Y
;time taken: 10min
;******************************** type definition part *******************************
(define-type Person
  [Professor (courses integer?)
             (projects integer?)]
  [UndergraduateStudent (courses integer?)]
  [GraduateStudent (courses integer?)
                   (papers integer?)])

(define prof1(Professor 2 2))
(define under1(UndergraduateStudent 6))
(define grad1(GraduateStudent 4 2))
(define grad2(GraduateStudent 4 3))
(define grad3(GraduateStudent 2 4))

;******************************** function part *******************************
;[contract]Person-> courses: Person->number
;[purpose] To get numbers of course who taken,taught
;[test] (test (have-courses prof1) 2)
;       (test (have-courses under1) 6)
;       (test (have-courses grad3) 2)
(define (have-courses p)
  (type-case Person p
        [Professor (c p) c]
        [UndergraduateStudent (c) c]
        [GraduateStudent (c p) c]))

(test (have-courses prof1) 2)
(test (have-courses under1) 6)
(test (have-courses grad3) 2)

;[contract]Person-> ready for graduate: Person->boolean
;[purpose] To know wheter person is ready to graduate
;[test] (test (ready-to-graduate under1) #f)
;       (test (ready-to-graduate grad1) #f)
;       (test (ready-to-graduate grad2) #t)
;       (test (ready-to-graduate grad3) #t)
(define (ready-to-graduate p)
  (type-case Person p
        [Professor (c p) #f]
        [UndergraduateStudent (c) #f]
        [GraduateStudent (c p) (>= p 3)]))

(test (ready-to-graduate under1) #f)
(test (ready-to-graduate grad1) #f)
(test (ready-to-graduate grad2) #t)
(test (ready-to-graduate grad3) #t)

;problem 7***************************************************
;solved by myself: Y
;time taken: 15 min
;[contract]list of character-> list of name: list->list
;[purpose] To convert character list to name list
;[test] (test (name-alphabet (list 'a 'b 'c 'd)) (list 'alice 'unnamed 'cherry 'unnamed))
;       (test (name-alphabet (list 'j 'b 'k 'd 'a)) (list 'jc 'unnamed 'kate 'unnamed 'alice))
(define (name-alphabet lst)
  (cond
    [(empty? lst) empty]
    [(symbol=? (first lst) 'a) (append (list 'alice) (name-alphabet (rest lst)))]
    [(symbol=? (first lst) 'c) (append (list 'cherry) (name-alphabet (rest lst)))]
    [(symbol=? (first lst) 'j) (append (list 'jc) (name-alphabet (rest lst)))]
    [(symbol=? (first lst) 'k) (append (list 'kate) (name-alphabet (rest lst)))]
    [else (append (list 'unnamed) (name-alphabet (rest lst)))]))

(test (name-alphabet (list 'a 'b 'c 'd)) (list 'alice 'unnamed 'cherry 'unnamed))
(test (name-alphabet (list 'j 'b 'k 'd 'a)) (list 'jc 'unnamed 'kate 'unnamed 'alice))

;problem 8***************************************************
;solved by myself: Y
;I have reference of equal syntax in https://docs.racket-lang.org/reference/booleans.html
;time taken: 1hour
;[contract]lis->converted list name: list->list
;[purpose] To convert designated string to new string in list
;[test] (test (update-name 'hey 'hi (list 1 2 'hey 3 5 'hey))(list 1 2 'hi 3 5 'hi))
;       (test (update-name 'cherry 'claire (cons 'jc (cons 'cherry (cons 'kate empty)))) '(jc claire kate))
(define (update-name old new lst)
  (cond
    [(empty? lst) empty]
    [(equal? (first lst) old) (append (list new) (update-name old new (rest lst)))]
    [else (append (list (first lst)) (update-name old new (rest lst)))]))

(test (update-name 'hey 'hi (list 1 2 'hey 3 5 'hey))(list 1 2 'hi 3 5 'hi))
(test (update-name 'cherry 'claire (cons 'jc (cons 'cherry (cons 'kate empty)))) '(jc claire kate))