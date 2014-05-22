;; Exercise 2.26: Suppose we deﬁne x and y to be two lists:
;; (define x (list 1 2 3))
;; (define y (list 4 5 6))
;; What result is printed by the interpreter in response to eval-
;; uating each of the following expressions:
;; (append x y)
;; (cons x y)
;; (list x y)

(defvar x (list 1 2 3))
(defvar y (list 4 5 6))

(append x y)
(cons x y)
(list x y)
