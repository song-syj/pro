;; Exercise 1.23: The smallest-divisor procedure shown at the start
;; of this section does lots of needless testing: After it checks to
;; see if the number is divisible by 2 there is no point in checking
;; to see if it is divisible by any larger even numbers. This suggests
;; that the values used for test-divisor should not be 2, 3, 4, 5, 6,
;; . . ., but rather 2, 3, 5, 7, 9, . . ..

(defun square (x)
  (* x x))

(defun smallest-divisor (n)
  (find-divisor n 2))

(defun find-divisor (n test-divisor)
  (cond ((> (square test-divisor) n) n)
		((divides? test-divisor n) test-divisor)
		(t (find-divisor n (next test-divisor)))))

(defun next (x)
  (if (= x 2)
	  3
	  (+ x 2)))

(defun divides? (a b)
  (= (mod b a) 0))

(defun prime? (n)
  (= (smallest-divisor n) n))

(defun timed-prime-test (n)
  (start-prime-test n (get-internal-run-time)))

(defun start-prime-test (n start-time)
	(if (prime? n)
		(report-prime n (- (get-internal-run-time) start-time))))


(defun report-prime (n elapsed-time)
  (terpri)
  (princ n)
  (princ " *** ")
  (princ elapsed-time))

(defun search-for-primes-iter (start number)
  (cond ((<= number 0) nil)
		((timed-prime-test start) (search-for-primes-iter (+ start 2) (- number 1)))
		(t (search-for-primes-iter (+ start 2) number))))

(defun first-odd (x)
  (if (evenp x)
	  (+ x 1)
	  (+ x)))

(defun search-for-primes(start number)
  (search-for-primes-iter (first-odd start) number))
