;; Exercise 2.57: Extend the differentiation program to han-
;; dle sums and products of arbitrary numbers of (two or more)
;; terms. en the last example above could be expressed as
;; (deriv '(* x y (+ x 3)) 'x)
;; Try to do this by changing only the representation for sums
;; and products, without changing the deriv procedure at all.
;; For example, the addend of a sum would be the first term,
;; and the augend would be the sum of the rest of the terms.

(defun augend (exp)
  (if (null (cdddr exp))
	  (caddr exp)
	  (cons '+ (cddr exp))))

(defun multiplicand (exp)
  (if (null (cdddr exp))
	  (caddr exp)
	  (cons '* (cddr exp))))

(defun make-sum (&rest nums)
  (let ((all (reduce #'+ (remove-if-not #'numberp nums)))
		(remain (remove-if #'numberp nums)))
	(cond ((null remain) all)
		  ((or (= all 0) (null all))
		   (if (null (cdr remain))
			   (car remain)
			   (append (list '+) remain)))
		  (t (append (list '+) (list all) remain)))))

(defun make-product (&rest nums)
  (let ((all (reduce #'* (remove-if-not #'numberp nums)))
		(remain (remove-if #'numberp nums)))
	(cond ((null remain) all)
		  ((or (= all 0) (null all))
		   (if (null (cdr remain))
			   (car remain)
			   (append (list '*) remain)))
		  (t (append (list '*) (list all) remain)))))
