;; Exercise 1.36: Modify fixed-point so that it prints the
;; sequence of approximations it generates, using the newline
;; and display primitives shown in Exercise 1.22. Then find
;; a solution to x x = 1000 by finding a fixed point of x →
;; log(1000)/ log(x). (Use Scheme’s primitive log procedure,
;; which computes natural logarithms.) Compare the number
;; of steps this takes with and without average damping. (Note
;; that you cannot start fixed-point with a guess of 1, as this
;; would cause division by log(1) = 0.)

(defun fixed-point (f first-guess)
  (labels ((close-enough? (v1 v2)
		   (< (abs (- v1 v2)) (* v1 1e-10)))
		   (try (guess num)
			 (let ((next (funcall f guess)))
			   (format t "guess ~A: ~A~%" num next)
			   (if (close-enough? next guess)
				   next
				   (try next (+ num 1))))))
	(try first-guess 1)))

(defun average (x y)
  (/ (+ x y) 2))

(fixed-point #'(lambda (x) (/ (log 1000) (log x))) 10.00d0)
(fixed-point #'(lambda (x) (average x (/ (log 1000) (log x)))) 10.00d0)
