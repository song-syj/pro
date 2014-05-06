;; Exercise 1.28:      Modify the expmod procedure to signal
;; if it discovers a nontrivial square root of 1, and use
;; this to implement the Miller-Rabin test with a procedure
;; analogous to fermat-test. Check your procedure by testing
;; various known primes and non-primes.


(defun expmod-trivial (base exp m)
  (labels ((trivial-check (x square)
			 (if (and (= square 1)
					  (/= x 1)
					  (/= x (- m 1)))
				 0
				 square))
		   (squaremod-with-check (x)
			 (trivial-check x (mod (square x) m))))
	(cond ((= exp 0) 1)
		  ((evenp exp)
		   (squaremod-with-check
			(expmod-trivial base (/ exp 2) m)))
		  (t (mod (* base (expmod-trivial base (- exp 1) m)) m)))))


(defun miller-rabin-test (n)
  (labels ((try-it (a)
			 (= (expmod-trivial a (- n 1) n) 1)))
	(try-it (+ 1 (random (- n 1))))))


(defun miller-rabin-prime? (n times)
  (cond ((= times 0) t)
		((miller-rabin-test n) (fast-prime? n (- times 1)))
		(t nil)))


(defun prime-check? (n)
  (do ((i 3 (+ i 2)))
	  ((> i n) t)
	(if (null (eql (miller-rabin-prime? i 100) (prime? i)))
		(return i))))
