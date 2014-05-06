;; Exercise 1.22: Most Lisp implementations include a primitive
;; called runtime that returns an integer that specifies
;; the amount of time the system has been running (measured,
;; for example, in microseconds). The following timed prime-test
;; procedure, when called with an integer n, prints n and checks
;; to see if n is prime. If n is prime, the procedure prints three
;; asterisks followed by the amount of time used in performing the test.

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

;; Using this procedure, write a procedure search-for-primes
;; that checks the primality of consecutive odd integers in a
;; specified range. Use your procedure to find the three small-
;; est primes larger than 1000; larger than 10,000; larger than
;; 100,000; larger than 1,000,000. Note the time needed to test
;; each prime. Since the testing algorithm has order of growth
;;  of Θ(√n), you should expect that testing for primes around
;; 10,000 should take about √10 times as long as testing for
;; primes around 1000. Do your timing data bear this out?
;; How well do the data for 100,000 and 1,000,000 support the
;; √Θ( n) prediction? Is your result compatible with the notion
;; that programs on your machine run in time proportional to
;; the number of steps required for the computation?

(defun search-for-primes-iter (start number)
  (cond ((<= number 0) nil)
		((time-prime-test start) (search-for-primes-iter (+ start 2) (- number 1)))
		(t (search-for-primes-iter (+ start 2) number))))

(defun first-odd (x)
  (if (evenp x)
	  (+ x 1)
	  (+ x)))

(defun search-for-primes (start number)
  (search-for-primes-iter (first-odd start) number))

;; Programs on my machine run in time proportional to
;; the number of steps required for the computation
