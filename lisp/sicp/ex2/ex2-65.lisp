;; Exercise 2.65: Use the results of Exercise 2.63 and Exer-
;; cise 2.64 to give Θ(n) implementations of union-set and
;; intersection-set for sets implemented as (balanced) bi-
;; nary trees.

(defun union-set (set1 set2)
  (let ((lst1 (tree->list-2 set1))
		(lst2 (tree->list-2 set2)))
	(list->tree (union-list lst1 lst2))))

(defun intersection-set (set1 set2)
  (let ((lst1 (tree->list-2 set1))
		(lst2 (tree->list-2 set2)))
	(list->tree (intersection-list lst1 lst2))))

(defun union-list (lst1 lst2)
  (if (or (null lst1) (null lst2))
	  (append lst1 lst2)
	  (let ((x1 (car lst1))
			(x2 (car lst2)))
		(cond ((= x1 x2) (cons x1 (union-list (cdr lst1)
											 (cdr lst2))))
			  ((< x1 x2) (cons x1 (union-list (cdr lst1)
											 lst2)))
			  ((> x1 x2) (cons x2 (union-list lst1 (cdr lst2))))))))

(defun intersection-list (lst1 lst2)
  (if (or (null lst1) (null lst2))
	  nil
	  (let ((x1 (car lst1))
			(x2 (car lst2)))
		(cond ((= x1 x2) (cons x1 (intersection-list (cdr lst1)
													 (cdr lst2))))
			  ((< x1 x2) (intersection-list (cdr lst1)
											lst2))
			  ((> x1 x2) (intersection-list lst1 (cdr lst2)))))))






