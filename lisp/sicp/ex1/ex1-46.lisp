;; Exercise 1.46: Several of the numerical methods described
;; in this chapter are instances of an extremely general
;; computational strategy known as iterative improvement.
;; Iterative improvement says that, to compute something, we
;; start with an initial guess for the answer, test if the
;; guess is good enough, and otherwise improve the guess and
;; continue the process using the improved guess as the new
;; guess. Write a procedure iterative-improve that takes two
;; procedures as arguments: a method for telling whether a
;; guess is good enough and a method for improving a guess.
;; Iterative-improve should return as its value a procedure
;; that takes a guess as argument and keeps improving the
;; guess until it is good enough. Rewrite the sqrt procedure
;; of Section 1.1.7 and the fixed-point procedure of Section
;; 1.3.3 in terms of iterative-improve.

(defun iterative-improve (enough-close? improve)
  (labels ((iter-check (guess)
			 (let ((next-guess (funcall improve guess)))
			   (if (funcall enough-close? next-guess guess)
				   next-guess
				   (iter-check next-guess)))))
	(lambda (guess)
	  (iter-check guess))))

(defun fixed-point-iter (f guess)
  (labels ((close-enough? (v1 v2)
			 (< (abs (- v1 v2)) 1e-12)))
	(funcall (iterative-improve #'close-enough? f) guess)))

(defun sqrt-iter (guess x)
  (labels ((close-enough? (v1 v2)
			 (< (abs (- v1 v2)) 1e-12)))
	(funcall (iterative-improve #'close-enough?
								#'(lambda (y) (average y (/ x y))))
			 guess)))
(defun sqrt-improve (x)
  (sqrt-iter 1.0d0 x))

(defun average (x y)
  (/ (+ x y) 2))

(defun square (x)
  (* x x))

