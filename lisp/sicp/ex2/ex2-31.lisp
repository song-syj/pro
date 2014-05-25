;; Exercise 2.31: Abstract your answer to Exercise 2.30 to
;; produce a procedure tree-map with the property that square-
;; tree could be deﬁned as
;; (define (square-tree tree) (tree-map square tree))

(defun tree-map (proc tree)
  (mapcar #'(lambda (x)
			  (if (atom x)
				  (funcall proc x)
				  (square-tree x)))
		  tree))

(defun square-tree (tree)
  (tree-map #'square tree))


