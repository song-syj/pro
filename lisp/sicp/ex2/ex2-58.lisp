;; Exercise 2.58: Suppose we want to modify the differentia-
;; tion program so that it works with ordinary mathematical
;; notation, in which + and * are infix rather than prefix opera-
;; tors. Since the differentiation program is defined in terms of
;; abstract data, we can modify it to work with different repre-
;; sentations of expressions solely by changing the predicates,
;; selectors, and constructors that define the representation of
;; the algebraic expressions on which the differentiator is to
;; operate.
;; a. Show how to do this in order to differentiate algebraic
;; expressions presented in infix form, such as (x + (3
;; * (x + (y + 2)))) . To simplify the task, assume that
;; + and * always take two arguments and that expres-
;; sions are fully parenthesized.
;; b. e problem becomes substantially harder if we allow
;; standard algebraic notation, such as (x + 3 * (x +
;; y + 2)) , which drops unnecessary parentheses and
;; assumes that multiplication is done before addition.
;; Can you design appropriate predicates, selectors, and
;; constructors for this notation such that our derivative
;; program still works?

(defun number? (x) (numberp x))
(defun varible? (x) (symbolp x))
(defun same-varible? (v1 v2)
  (and (varible? v1) (varible? v2) (eql v1 v2)))


(defun deriv-infix (exp var)
  (cond ((number? exp) 0)
		((varible? exp) (if (same-varible? exp var) 1 0))
		((sum-infix? exp)
		 (make-sum-infix (deriv-infix (addend-infix exp) var)
						 (deriv-infix (augend-infix exp) var)))
		((product-infix? exp)
		 (make-sum-infix (make-product-infix (multiplier-infix exp)
											 (deriv-infix (multiplicand-infix exp) var))
						 (make-product-infix (deriv-infix (multiplier-infix exp) var)
											 (multiplicand-infix exp))))
		(t (error "unknown expression type: DRIVE ~A" exp))))

(defun sum-infix? (exp)
  (and (consp exp) (eql (cadr exp) '+)))

(defun product-infix? (exp)
  (and (consp exp) (eql (cadr exp) '*)))

(defun =number? (exp num)
  (and (number? exp) (= exp num)))

(defun make-sum-infix (addend augend)
  (cond ((=number? addend 0) augend)
		((=number? augend 0) addend)
		((and (number? augend) (number? addend) (+ addend augend)))
		(t (list addend '+ augend))))

(defun make-product-infix (multiplier multiplicand)
  (cond ((or (=number? multiplier 0) (=number? multiplicand 0)) 0)
		((=number? multiplier 1) multiplicand)
		((=number? multiplicand 1) multiplier)
		((and (number? multiplier) (number? multiplicand) (+ multiplier multiplicand)))
		(t (list multiplier '* multiplicand))))
  
(defun addend-infix (x)
  (car x))
(defun augend-infix (x)
  (caddr x))

(defun multiplier-infix (x)
  (car x))
(defun multiplicand-infix (x)
  (caddr x))

;;; part B
;;;  redefine addend augend sum? product? because of
;;; the priority or + and * operation

(defun sum-infix? (exp)
  (and (consp exp) (eql (operation exp) '+)))

(defun augend-infix (exp)
  (let ((aug (cdr (member '+ exp))))
	(if (null (cdr aug))
		(car aug)
		aug)))

(defun addend-infix (exp)
  (labels ((iter (expr acc)
			 (if (eql (car expr) '+)
				 acc
				 (iter (cdr expr) (append acc (list (car expr)))))))
	(let ((result (iter exp nil)))
	  (if (null (cdr result))
		  (car result)
		  result))))


(defun product-infix? (exp)
  (and (consp exp) (eql (operation exp) '*)))

(defun multiplicand-infix (exp)
  (let ((cand (cdr (member '* exp))))
	(if (null (cdr cand))
		(car cand)
		cand)))

(defun multiplier-infix (exp)
  (labels ((iter (expr acc)
			 (if (eql (car expr) '*)
				 acc
				 (iter (cdr expr) (append acc (list (car expr)))))))
	(let ((result (iter exp nil)))
	  (if (null (cdr result))
		  (car result)
		  result))))

(defun operation (exp)
  (if (member '+ exp)
	  '+
	  '*))
