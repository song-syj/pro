;; Exercise 1.40: Define a procedure cubic that can be used
;; together with the newtons-method procedure in expressions
;; of the form
;; (newtons-method (cubic a b c) 1)
;; to approximate zeros of the cubic x 3 + ax 2 + bx + c.

(defun average-damp (f)
  (lambda (x) (average x (funcall f x))))

(defun average (x y)
  (/ (+ x y) 2))

(defun square (x)
  (* x x))

(funcall (average-damp #'square) 10)

(defun fixed-point (f first-guess)
  (labels ((close-enough? (v1 v2)
		   (< (abs (- v1 v2)) 1e-12))
		   (try (guess)
			 (let ((next (funcall f guess)))
			   (if (close-enough? next guess)
				   next
				   (try next)))))
	(try first-guess)))

(defun sqrt-damp (x)
  (fixed-point (average-damp #'(lambda (y) (/ x y))) 1.0d0))

(defun cube-root (x)
  (fixed-point (average-damp #'(lambda (y) (/ x (square y)))) 1.0d0))

(defvar *dx* 0.0001)
(defun deriv (g)
	(lambda (x)
	  (/ (- (funcall g (+ x *dx*)) (funcall g x)) *dx*)))

(defun cube (x)
  (* x x x))

(defun newton-transform (g)
  (lambda (x)
	(- x (/ (funcall g x) (funcall (deriv g) x)))))

(defun newtons-method (g guess)
  (fixed-point (average-damp (newton-transform g)) guess))

(defun cubic (a b c)
  (lambda (x)
	(+ (* x x x) (* a x x) (* b x) c)))
