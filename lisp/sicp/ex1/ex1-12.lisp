;; Exercise 1.12: Write a procedure that computes elements of
;; Pascal’s triangle by means of a recursive process
(defun pascal-triangle (m n)
  (cond ((= m 0) 1)
		((= m n) 1)
		(t (+ (pascal-triangle m (- n 1))
			  (pascal-triangle (- m 1) (- n 1))))))

(defun print-pascal (n)
  (do ((i 0 (+ i 1)))
	  ((> i n))
	(do ((j 0 (+ j 1)))
		((> j i))
	  (format t "~02A " (pascal-triangle j i)))
	(format t "~%")))
