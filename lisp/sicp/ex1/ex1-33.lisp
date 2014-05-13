;; Exercise 1.33: You can obtain an even more general version of
;; accumulate (Exercise 1.32) by introducing the notion of a filter
;; on the terms to be combined. That is, combine only those terms
;; derived from values in the range that satisfy a specified
;; condition. The resulting filtered-accumulate abstraction takes
;; the same arguments as accumulate, together with an additional
;; predicate of one argument that specifies the filter. Write
;; filtered-accumulate as a procedure. Show how to express the
;; following using filtered accumulate:
;; a. the sum of the squares of the prime numbers in the interval
;; a to b (assuming that you have a prime? predicate already written)
;; b. the product of all the positive integers less than n that
;; are relatively prime to n (i.e., all positive integers i < n
;; such that GCD(i, n) = 1).

(defun filtered-accumulate (predicate combiner null-value term a next b)
  (if (> a b)
	  null-value
	  (filtered-accumulate predicate
						   combiner
						   (if (funcall predicate a)
							   (funcall combiner (funcall term a) null-value)
							   null-value)
						   term
						   (funcall next a) next b)))

(defun square (x)
  (* x x))

(defun smallest-divisor (n)
  (find-divisor n 2))

(defun find-divisor (n test-divisor)
  (cond ((> (square test-divisor) n) n)
		((divides? test-divisor n) test-divisor)
		(t (find-divisor n (+ test-divisor 1)))))

(defun divides? (a b)
  (= (mod b a) 0))

(defun prime? (n)
  (= (smallest-divisor n) n))

(defun prim-sum (a b)
  (filtered-accumulate #'prime? #'+ 0 #'identity a #'(lambda (x) (+ x 1)) b))

(defun relative-prime-product (n)
  (filtered-accumulate #'(lambda (x)
						   (= (gcd x n) 1))
					   #'* 1 #'identity 1
					   #'(lambda (x) (+ x 1)) (- n 1)))
