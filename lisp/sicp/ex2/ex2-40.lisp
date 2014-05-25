;; Exercise 2.40: Define a procedure unique-pairs that, given
;; an integer n, generates the sequence of pairs (i, j) with 1 ≤
;; j < i ≤ n. Use unique-pairs to simplify the definition of
;; prime-sum-pairs given above.

(defun unique-pairs (n)
  (flatmap #'(lambda (i)
			   (mapcar #'(lambda (j)
						   (list j i))
					   (enumerate-interval 1 (- i 1))))
		   (enumerate-interval 1 n)))

(defun prime-sum-pairs (n)
  (mapcar #'make-pair-sum
		  (filter #'prime-sum?
				  (unique-pairs n))))


