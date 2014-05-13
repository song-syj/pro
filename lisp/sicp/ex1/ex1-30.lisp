;; Exercise 1.30: The sum procedure above generates a linear
;; recursion. The procedure can be rewriten so that the sum
;; is performed iteratively.

(defun sum (term a next b)
	(labels ((iter (a result)
			   (if (> a b)
				   result
				   (iter (funcall next a) (+ (funcall term a) result)))))
	  (iter a 0)))

(defun pi-sum (a b)
  (sum #'(lambda (x)
		   (/ 1.0 x (+ x 2)))
	   a
	   #'(lambda (x) (+ x 4))
	   b))
	   
