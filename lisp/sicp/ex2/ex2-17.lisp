;; Exercise 2.17: Deﬁne a procedure last-pair that returns
;; the list that contains only the last element of a given (nonempty)
;; list:
;; (last-pair (list 23 72 149 34))
;; (34)

(defun last-pair (lst)
  (if (null (cdr lst))
	  lst
	  (last-pair (cdr lst))))

