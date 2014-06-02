;; Exercise 2.56: Show how to extend the basic differentiator
;; to handle more kinds of expressions. For instance, imple-
;; ment the differentiation rule
;; d(u^n)/du = n*u^(n −1)*du/dx
;; by adding a new clause to the deriv program and defining
;; appropriate procedures exponentiation? , base , exponent ,
;; and make-exponentiation . (You may use the symbol **
;; to denote exponentiation.) Build in the rules that anything
;; raised to the power 0 is 1 and anything raised to the power
;; 1 is the thing itself.

(defun exponentiation? (exp)
  (and (consp exp) (eql (car exp) '**)))

(defun exponent (p)
  (caddr p))

(defun base (p)
  (cadr p))

(defun make-exponentiation (base exponent)
  (cond ((= exponent 0) 1)
		((= exponent 1) base)
		(t (list '** base exponent))))
