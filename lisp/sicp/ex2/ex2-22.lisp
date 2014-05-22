;; Exercise 2.22: Louis Reasoner tries to rewrite the ﬁrst square-
;; list procedure of Exercise 2.21 so that it evolves an itera-
;; tive process:
;; (define (square-list items)
;; 	(define (iter things answer)
;; 		(if (null? things)
;; 			answer
;; 			(iter (cdr things)
;; 				  (cons (square (car things))
;; 						answer))))
;;   (iter items nil))
;; Unfortunately, deﬁning square-list this way produces the
;; answer list in the reverse order of the one desired. Why?
;; Louis then tries to ﬁx his bug by interchanging the argu-
;; ments to cons :
;; (define (square-list items)
;; 	  (define (iter things answer)
;; 		   (if (null? things)
;; 			   answer
;; 			   (iter (cdr things)
;; 					 (cons answer
;; 						   (square (car things))))))
;; 	(iter items nil))
;; This doesn’t work either. Explain.

(defun square-list (items)
  (labels ((iter (things answer)
			 (if (null things)
				 answer
				 (iter (cdr things)
					   (append answer (list (square (car things))))))))
	(iter (cdr items) (list (car items)))))
