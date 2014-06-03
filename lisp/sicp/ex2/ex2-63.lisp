;; Figure 2.17: Unbalanced tree produced by adjoining 1
;; through 7 in sequence.
;; (define (tree->list-1 tree)
;; 	'()
;;   (append (tree->list-1 (left-branch tree))
;; 		  (cons (entry tree)
;; 				(tree->list-1
;; 				 (right-branch tree)))))
;; (define (tree->list-2 tree)
;; 	(define (copy-to-list tree result-list)
;; 		(if (null? tree)
;; 			result-list
;; 			(copy-to-list (left-branch tree)
;; 						  (cons (entry tree)
;; 								(copy-to-list
;; 								 (right-branch tree)
;; 								 result-list)))))
;;   (copy-to-list tree '()))
;; a. Do the two procedures produce the same result for
;; every tree? If not, how do the results differ? What lists
;; 214do the two procedures produce for the trees in Figure
;; 2.16?
;; b. Do the two procedures have the same order of growth
;; in the number of steps required to convert a balanced
;; tree with n elements to a list? If not, which one grows
;; more slowly?

(defun tree->list-1 (tree)
  (if (null tree)
	  nil
	  (append (tree->list-1 (left-branch tree))
			  (cons (entry tree)
					(tree->list-1 (right-branch tree))))))

(defun tree->list-2 (tree)
  (labels ((copy-to-list (tree result-list)
			 (if (null tree)
				 result-list
				 (copy-to-list (left-branch tree)
							   (cons (entry tree)
									 (copy-to-list (right-branch tree)
												   result-list))))))
	(copy-to-list tree nil)))

;;; part b
;;; tree->list-1 : T(n) = 2T(n/2) + O(n/2) => T(n) = O(nlog(n))
;;; tree->list-2 : T(n) = 2T(n/2) + O(1) => T(n) = O(n)
;;; note: append has the cost O(n/2)

