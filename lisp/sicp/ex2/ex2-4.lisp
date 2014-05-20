;; Exercise 2.4: Here is an alternative procedural representa-
;; tion of pairs. For this representation, verify that (car (cons
;; x y)) yields x for any objects x and y .
;; (define (cons x y)
;; 	(lambda (m) (m x y)))
;; (define (car z)
;; 	(z (lambda (p q) p)))
;; What is the corresponding deﬁnition of cdr ? (Hint: To ver-
;; ify that this works, make use of the substitution model of
;; Section 1.1.5.)

(defun cons2 (x y)
  (lambda (m) (funcall m x y)))

(defun car2 (z)
  (funcall z #'(lambda (p q) p)))

(defun cdr2 (z)
  (funcall z #'(lambda (p q) q)))

  
