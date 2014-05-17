;; Exercise 1.44: The idea of smoothing a function is an important
;; concept in signal processing. If f is a function and dx is some
;; small number, then the smoothed version of f is the function
;; whose value at a point x is the average of f (x − dx), f (x),
;; and f (x +dx). Write a procedure smooth that takes as input a
;; procedure that computes f and returns a procedure that computes
;; the smoothed f . It is sometimes valuable to repeatedly smooth a
;; function (that is, smooth the smoothed function, and so on) to
;; obtain the n-fold smoothed function. Show how to generate the
;; n-fold smoothed function of any given function using smooth and
;; repeated from Exercise 1.43.
(defun compose (f g)
  (lambda (x)
	(funcall f (funcall g x))))

(defun repeated (f n)
  (if (<= n 1)
	  f
	  (compose f (repeated f (- n 1)))))

(defun repeated-iter (f n)
  (labels ((f-iter (m combine)
			 (if (= n m)
				 combine
				 (f-iter (+ m 1) (compose f combine)))))
	(f-iter 1 f)))

(defun smooth (f)
  (let ((dx 0.0001))
	(lambda (x)
	  ((lambda (a b c) (/ (+ a b c) 3.0d0))
	   (funcall f x)
	   (funcall f (+ x dx))
	   (funcall f (- x dx))))))

(defun smooth-n-times (f n)
  (funcall (repeated-iter #'smooth n) f))

(defun impulse (x)
  (if (= x 0)
	  20
	  0))
