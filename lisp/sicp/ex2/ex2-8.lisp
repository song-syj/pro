;; Exercise 2.8: Using reasoning analogous to Alyssa’s, de-
;; scribe how the difference of two intervals may be com-
;; puted. Define a corresponding subtraction procedure, called
;; sub-interval.

(defun sub-interval (x y)
  (make-interval (- (lower-bound x) (upper-bound y))
				 (- (upper-bound x) (lower-bound y))))
