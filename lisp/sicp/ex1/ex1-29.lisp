;; Exercise 1.29: Simpson’s Rule is a more accurate method
;; of numerical integration than the method illustrated above.
;; Using Simpson’s Rule, the integral of a function f between
;; a and b is approximated as
;; h/3 * (y0 + 4y1 + 2y2 + 4y3 + 2y4 + · · · + 2yn −2 + 4yn −1 + yn ),
;; where h = (b − a)/n, for some even integer n, and yk =f(a+kh).
;; (Increasing n increases the accuracy of the approximation.)
;; Define a procedure that takes as arguments f , a, b, and n
;; and returns the value of the integral, computed using Simpson’s Rule.
;; Use your procedure to integrate cube between 0 and 1
;; (with n = 100 and n = 1000),and compare the results to those of
;; the integral procedure shown above.

(defun sum (term a next b)
  (if (> a b)
	  0
	  (+ (funcall term a)
		 (sum term (funcall next a) next b))))

(defun inc (n) (+ n 1))
(defun cube (x)
  (* x x x))

(defun simpson-integral (f a b n)
  (let ((h (/ (- b a) n)))
	(* (/ h 3.0)
	   (sum #'(lambda (x)
				(let ((y (funcall f (+ a (* x h)))))
				  (cond ((or (= x 0) (= x n)) y)
						((oddp x) (* y 4))
						(t (* 2 y)))))
			0 #'inc n))))

