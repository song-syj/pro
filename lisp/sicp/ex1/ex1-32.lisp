;; Exercise 1.32: a. Show that sum and product (Exercise 1.31)
;; are both special cases of a still more general notion called
;; accumulate that combines a collection of terms, using some
;; general accumulation function:
;; (accumulate combiner null-value term a next b)
;; Accumulate takes as arguments the same term and range
;; specifications as sum and product, together with a combiner
;; procedure (of two arguments) that specifies how the current
;; term is to be combined with the accumulation of the preceding
;; terms and a null-value that specifies what base value to use
;; when the terms run out. Write accumulate and show how sum and
;; product can both be defined as simple calls to accumulate

(defun accumulate (combiner null-value term a next b)
  (if (> a b)
	  null-value
	  (funcall combiner
			   (funcall term a)
			   (accumulate combiner null-value term (funcall next a) next b))))

(defun sum (term a next b)
  (accumulate #'+ 0 term a next b))

(defun product (term a next b)
  (accumulate #'* 1 term a next b))

(defun accumulate-iter (combiner null-value term a next b)
  (if (> a b)
	  null-value
	  (accumulate-iter combiner
					   (funcall combiner
								null-value
								(funcall term a))
					   term (funcall next a) next b)))


