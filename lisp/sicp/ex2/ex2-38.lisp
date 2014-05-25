;; Exercise 2.38: The accumulate procedure is also known as
;; fold-right , because it combines the ﬁrst element of the se-
;; quence with the result of combining all the elements to the
;; right. There is also a fold-left , which is similar to fold-
;; right , except that it combines elements working in the op-
;; posite direction:
;; (define (fold-left op initial sequence)
;; 	(define (iter result rest)
;; 		(if (null? rest)
;; 			result
;; 			(iter (op result (car rest))
;; 				  (cdr rest))))
;;   (iter initial sequence))
;; What are the values of
;; (fold-right / 1 (list 1 2 3))
;; (fold-left / 1 (list 1 2 3))
;; (fold-right list nil (list 1 2 3))
;; (fold-left list nil (list 1 2 3))
;; Give a property that op should satisfy to guarantee that
;; fold-right and fold-left will produce the same values
;; for any sequence.

(defun fold-right (op initial sequence)
  (if (null sequence)
	  initial
	  (funcall op
			   (car sequence)
			   (fold-right op initial (cdr sequence)))))

(defun fold-left (op initial sequence)
  (labels ((iter (result subseq)
				(if (null subseq)
					result
					(iter (funcall op result (car subseq))
						  (cdr subseq)))))
	(iter initial sequence)))

(fold-right #'/ 1 (list 1 2 3))
(fold-left #'/ 1 (list 1 2 3))
(fold-right #'list nil (list 1 2 3))
(fold-left #'list nil (list 1 2 3))

;;commutative law
