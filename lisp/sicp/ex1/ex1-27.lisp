;; Exercise 1.27: Demonstrate that the Carmichael numbers listed
;; in Footnote 1.47 really do fool the Fermat test. That is,write
;; a procedure that takes an integer n and tests whether an is
;; congruent to a modulo n for every a < n, and try your procedure
;; on the given Carmichael numbers.

(defun expmod (base exp m)
	(cond ((= exp 0) 1)
		  ((evenp exp) (mod (square (expmod base (/ exp 2) m))
							m))
		  (t (mod (* base (expmod base (- exp 1) m)) m))))

(defun fermat-test (n)
  (labels ((try-it (a)
			 (= (expmod a n n) a)))
	(try-it (+ 1 (random (- n 1))))))

(defun fermat-try-all (n)
  (fermat-try-dec n (- n 1)))

(defun fermat-try-dec (n a)
  (cond ((= a 1) t)
		((not (fermat-try n a)) nil)
		(t (fermat-try-dec n (- a 1)))))

(defun fermat-try (n a)
  (= (expmod a n n) a))

