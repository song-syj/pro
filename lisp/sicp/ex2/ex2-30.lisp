;; Exercise 2.30: Deﬁne a procedure square-tree analogous
;; to the square-list procedure of Exercise 2.21. at is, square-
;; tree should behave as follows:
;; (square-tree
;; (list 1
;; (list 2 (list 3 4) 5)
;; (list 6 7)))
;; (1 (4 (9 16) 25) (36 49))
;; Deﬁne square-tree both directly (i.e., without using any
;; higher-order procedures) and also by using map and recur-
;; sion.

(defun square (x)
  (* x x))

(defun square-tree (tree)
  (cond ((null tree) nil)
		((atom tree) (square tree))
		(t (cons (square-tree (car tree))
				 (square-tree (cdr tree))))))

(defun square-tree (tree)
  (mapcar #'(lambda (x)
			  (if (atom x)
				  (square x)
				  (square-tree x)))
		  tree))
