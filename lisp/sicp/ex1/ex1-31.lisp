;; Exercise 1.31:
;; a. The sum procedure is only the simplest of a vast number
;; of similar abstractions that can be captured as higherorder
;; procedures.51 Write an analogous procedure called product
;; that returns the product of the values of a function at points
;; over a given range. Show how to define factorial in terms of
;; product. Also use product to compute approximations to π using
;; the formula:
;; pi/2 = 2 · 4 · 4 · 6 · 6 · 8···
;; ------------------------------
;; 4 3 · 3 · 5 · 5 · 7 · 7···
;; b. If your product procedure generates a recursive process,
;; write one that generates an iterative process. If it generates
;; an iterative process, write one that generates a recursive process.

(defun product (term a next b)
  (if (> a b)
	  1
	  (* (funcall term a) (product term (funcall next a) next b))))

(defun pi-product (a b)
  (labels ((term (x)
			 (if (oddp x)
				 (/ (+ x 1.0) (+ x 2))
				 (/ (+ x 2.0) (+ x 1))))
		   (next (x)
			 (+ x 1)))
	(product #'term a #'next b)))

(defun product-iter (term a next b r)
  (if (> a b)
	  r
	  (product-iter term (funcall next a) next b (* (funcall term a) r))))

(defun pi-product (b)
  (labels ((term (x)
			 (if (oddp x)
				 (/ (+ x 1.0d0) (+ x 2.0d0))
				 (/ (+ x 2.0d0) (+ x 1.0d0))))
		   (next (x)
			 (+ x 1)))
	(product-iter #'term 1 #'next b 1.0d0)))


