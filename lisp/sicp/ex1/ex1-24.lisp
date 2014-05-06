;; Exercise 1.24: Modify the timed-prime-test procedure of
;; Exercise 1.22 to use fast-prime? (the Fermat method), and
;; test each of the 12 primes you found in that exercise. Since
;; the Fermat test has Θ(log n) growth, how would you expect
;; the time to test primes near 1,000,000 to compare with the
;; time needed to test primes near 1000? Do your data bear
;; this out? Can you explain any discrepancy you find?

(defun timed-prime-test-fast (n)
  (start-prime-test-fast n (get-internal-run-time)))

(defun start-prime-test-fast (n start-time)
	(if (fast-prime? n 30)
		(report-prime n (- (get-internal-run-time) start-time))))


(defun report-prime (n elapsed-time)
  (terpri)
  (princ n)
  (princ " *** ")
  (princ elapsed-time))

(defun search-for-primes-iter-fast (start number)
  (cond ((<= number 0) nil)
		((timed-prime-test-fast start) (search-for-primes-iter-fast (+ start 2) (- number 1)))
		(t (search-for-primes-iter-fast (+ start 2) number))))

(defun first-odd (x)
  (if (evenp x)
	  (+ x 1)
	  (+ x)))

(defun expmod (base exp m)
	(cond ((= exp 0) 1)
		  ((evenp exp) (mod (square (expmod base (/ exp 2) m))
							m))
		  (t (mod (* base (expmod base (- exp 1) m)) m))))

(defun fermat-test (n)
  (labels ((try-it (a)
			 (= (expmod a n n) a)))
	(try-it (+ 1 (random (- n 1))))))


(defun fast-prime? (n times)
  (cond ((= times 0) t)
		((fermat-test n) (fast-prime? n (- times 1)))
		(t nil)))

(defun square (x)
  (* x x))

(defun search-for-primes-fast (start number)
  (search-for-primes-iter-fast (first-odd start) number))

