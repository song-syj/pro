;; Exercise 2.60: We specified that a set would be represented
;; as a list with no duplicates. Now suppose we allow dupli-
;; cates. For instance, the set {1, 2, 3} could be represented as
;; the list (2 3 2 1 3 2 2) . Design procedures element-
;; of-set? , adjoin-set , union-set , and intersection-set
;; that operate on this representation. How does the efficiency
;; of each compare with the corresponding procedure for the
;; non-duplicate representation? Are there applications for which
;; you would use this representation in preference to the non-
;; duplicate one?

(defun element-of-set? (x set)
  (cond ((null set) nil)
		((eql x (car set)) t)
		(t (element-of-set? x (cdr set)))))

(defun adjoin-set (x set)
  (cons x set))

(defun intersection-set (set1 set2)
  (cond ((or (null set1) (null set2)) nil)
		((element-of-set? (car set1) set2)
		 (cons (car set1)
			   (intersection-set (cdr set1) set2)))
		(t (intersection-set (cdr set1) set2))))

(defun union-set (set1 set2)
  (cond ((null set1) set2)
		((null set2) set1)
		(t (union-set  (cdr set1)
					   (adjoin-set (car set1) set2)))))

;;; for the condition where adjion-set and union-set is a frequent operation
