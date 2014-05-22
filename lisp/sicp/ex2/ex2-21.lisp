;; Exercise 2.21: The procedure square-list takes a list of
;; numbers as argument and returns a list of the squares of
;; those numbers.
;; (square-list (list 1 2 3 4))
;; (1 4 9 16)
;; Here are two diﬀerent deﬁnitions of square-list . Com-
;; plete both of them by ﬁlling in the missing expressions:
;; (define (square-list items)
;; 	(if (null? items)
;; 		nil
;; 		(cons ⟨ ?? ⟩ ⟨ ?? ⟩ )))
;; (define (square-list items)
;; 	(map ⟨ ?? ⟩ ⟨ ?? ⟩ ))

(defun square (x)
  (* x x))

(defun square-list (lst)
  (if (null lst)
	  nil
	  (cons (square (car lst))
			(square-list (cdr lst)))))

(defun square-list (lst)
  (mapcar #'square lst))

