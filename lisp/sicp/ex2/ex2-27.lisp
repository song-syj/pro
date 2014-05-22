;; Exercise 2.27: Modify your reverse procedure of Exercise
;; 2.18 to produce a deep-reverse procedure that takes a list
;; as argument and returns as its value the list with its ele-
;; ments reversed and with all sublists deep-reversed as well.
;; For example,
;; (define x (list (list 1 2) (list 3 4)))
;; x
;; ((1 2) (3 4))
;; (reverse x)
;; ((3 4) (1 2))
;; (deep-reverse x)
;; ((4 3) (2 1))

;; iterative impelement
(defun deep-reverse (lst)
  (labels ((iter-deep (lst acc)
			 (cond ((null lst) acc)
				   ((atom lst) lst)
				   (t (iter-deep (cdr lst)
								 (cons (iter-deep (car lst) nil)
									   acc))))))
	(iter-deep lst nil)))

;; recursive impelement
(defun deep-reverse (x) 
  (if (consp x) 
	  (append (deep-reverse (cdr x))  
			  (list (deep-reverse (car x)))) 
	  x)) 

