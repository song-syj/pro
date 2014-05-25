;; Exercise 2.41: Write a procedure to find all ordered triples
;; of distinct positive integers i, j, and k less than or equal to
;; a given integer n that sum to a given integer s.

(defun sum-tripiles (s)
  (filter #'(lambda (x)
			  (tripile-sum? x s)) (tripiles s)))

(defun tripile-sum? (tripile s)
  (= s (+ (first tripile) (second tripile) (third tripile))))

(defun tripiles (n)
  (flatmap #'(lambda (i)
			   (flatmap  #'(lambda (j)
							(mapcar #'(lambda (k)
										(list k j i))
									(enumerate-interval 1 (- j 1))))
						(enumerate-interval 1 (- i 1))))
		   (enumerate-interval 1 n)))
