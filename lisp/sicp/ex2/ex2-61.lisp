;; Exercise 2.61: Give an implementation of adjoin-set us-
;; ing the ordered representation. By analogy with element-
;; of-set? show how to take advantage of the ordering to
;; produce a procedure that requires on the average about half
;; as many steps as with the unordered representation.

(defun adjoin-set (x set)
  (cond ((null set) (cons x set))
		((= x (car set)) set)
		((< x (car set)) (cons x set))
		(t (cons (car set) (adjoin-set x (cdr set))))))

