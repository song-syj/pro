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

(defun newton-method (g guess)
  (fixed-point (average-damp (newton-transform g)) guess))

(defun sqrt-newtons (x)
  (newton-method #'(lambda (y) (- x (square y))) 1.0d0))

(defun fixed-point-of-transform (g transform guess)
  (fixed-point (funcall transform g) guess))

(defun sqrt-fix (x)
  (fixed-point-of-transform #'(lambda (y) (/ x y)) #'average-damp 1.0d0))

(defun sqrt-newtons (x)
  (fixed-point-of-transform #'(lambda (y) (- x (square y))) #'newton-transform 1.0d0))
