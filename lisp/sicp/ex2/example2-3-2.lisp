;; Example: Symbolic Differentiation


(defun deriv (exp var)
  (cond ((number? exp) 0)
		((varible? exp) (if (same-varible? exp var) 1 0))
		((sum? exp) (make-sum (deriv (addend exp) var)
							  (deriv (augend exp) var)))
		((product? exp)
		 (make-sum (make-product (multiplier exp)
								 (deriv (multiplicand exp) var))
				   (make-product (deriv (multiplier exp) var)
								 (multiplicand exp))))
		((exponentiation? exp)
		 (let ((n (exponent exp))
			   (u (base exp)))
		   (make-product n
						 (make-product
						  (make-exponentiation u (- n 1))
						  (deriv u var)))))
		(t (error "unknown expression type: DRIVE ~A" exp))))

(setf (symbol-function 'number?) #'numberp)
(defun varible? (x) (symbolp x))
(defun same-varible? (v1 v2)
  (and (varible? v1) (varible? v2) (eql v1 v2)))

;; (defun make-sum (a1 a2)
;;   (list '+ a1 a2))

;; (defun make-product (a1 a2)
;;   (list '* a1 a2))

(defun sum? (exp)
  (and  (consp exp) (eql (car exp) '+)))

(defun addend (s) (cadr s))
(defun augend (s) (caddr s))

(defun product? (exp)
  (and (consp exp) (eql (car exp) '*)))

(defun multiplier (p) (cadr p))
(defun multiplicand (p) (caddr p))

(defun make-sum (a1 a2)
  (cond ((=number? a1 0) a2)
		((=number? a2 0) a1)
		((and (number? a1) (number? a2))
		 (+ a1 a2))
		(t (list '+ a1 a2))))

(defun make-product (a1 a2)
  (cond ((or (=number? a1 0) (=number? a2 0)) 0)
		((=number? a1 1) a2)
		((=number? a2 1) a1)
		((and (number? a1) (number? a2))
		 (* a1 a2))
		(t (list  '* a1 a2))))

(defun =number? (exp num)
  (and (number? exp) (= exp num)))

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

