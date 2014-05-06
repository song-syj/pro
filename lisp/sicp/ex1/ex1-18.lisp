;; Exercise 1.18: Using the results of Exercise 1.16 and Exercise
;; 1.17, devise a procedure that generates an iterative process for
;; multiplying two integers in terms of adding, doubling, and halving
;; and uses a logarithmic number of steps.

(defun my-double (x)
  (* 2 x))
(defun my-halve (x)
  (/ x 2))
(defun fast-mul (a b)
  (fast-mul-iter a b 0))
(defun fast-mul-iter (a b s)
  (cond ((= b 0) s)
		((evenp b) (fast-mul-iter (my-double a) (my-halve b) s))
		(t (fast-mul-iter a (- b 1) (+ s a)))))
