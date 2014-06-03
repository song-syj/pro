;; Exercise 2.59: Implement the union-set operation for the
;; unordered-list representation of sets.
(defun union-set (set1 set2)
  (cond ((null set1) set2)
		((null set2) set1)
		(t (union-set  (cdr set1)
					   (adjoin-set (car set1) set2)))))
