;; Exercise 2.54: Two lists are said to be equal? if they con-
;; tain equal elements arranged in the same order. For exam-
;; ple,
;; (equal? '(this is a list) '(this is a list))
;; is true, but
;; (equal? '(this is a list) '(this (is a) list))
;; is false. To be more precise, we can deﬁne equal? recur-
;; sively in terms of the basic eq? equality of symbols by say-
;; ing that a and b are equal? if they are both symbols and
;; the symbols are eq? , or if they are both lists such that (car
;; a) is equal? to (car b) and (cdr a) is equal? to (cdr b) .
;; Using this idea, implement equal? as a procedure.

(defun equal? (a b)
  (cond ((null a) (null b))
		((and (symbolp a) (symbolp b)) (eql a b))
		((and (consp a) (consp b))
		 (and (equal? (car a) (car b))
			  (equal? (cdr a) (cdr b))))
		(t nil)))
