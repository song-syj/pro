;; Exercise 2.18: Deﬁne a procedure reverse that takes a list
;; as argument and returns a list of the same elements in re-
;; verse order:
;; (reverse (list 1 4 9 16 25))
;; (25 16 9 4 1)

(defun reverse-list (lst)
  (labels ((reverse-iter (lst acc)
			 (if (null lst)
				 acc
				 (reverse-iter (cdr lst) (cons (car lst) acc)))))
	(reverse-iter lst nil)))

