;; inding roots of equations by the half-interval method
(defun search-root (f neg-point pos-point)
	(let ((midpoint (average neg-point pos-point)))
	  (if (close-enough? neg-point pos-point)
		  midpoint
		  (let ((test-value (funcall f midpoint)))
			(cond ((plusp test-value)
				   (search-root f neg-point midpoint))
				  ((minusp test-value)
				   (search-root f midpoint pos-point))
				  (t midpoint))))))

(defun average (x y)
  (/ (+ x y) 2.0d0))

(defun close-enough? (x y)
  (< (abs (- x y)) 1e-10))

(defun  half-interval-method (f a b)
  (let ((a-value (funcall f a))
		(b-value (funcall f b)))
	(cond ((and (minusp a-value) (plusp b-value))
		   (search-root f a b))
		  ((and (plusp a-value) (minusp b-value))
		   (search-root f b a))
		  (t (error "~S ~S Values are not of opposite sign" a b)))))

;; Finding fixed points of functions

(defun fixed-point (f first-guess)
  (labels ((close-enough? (v1 v2)
		   (< (abs (- v1 v2)) 1e-12))
		   (try (guess)
			 (let ((next (funcall f guess)))
			   (if (close-enough? next guess)
				   next
				   (try next)))))
	(try first-guess)))

(defun fixed-sqrt (x)
  (fixed-point #'(lambda (y) (/ (+ y (/ x y)) 2)) 1.0d0))

 
