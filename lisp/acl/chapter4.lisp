;;1. Define a function to take a square array (an array whose dimensions
;;   are (n n)) and rotate it 90° clockwise

(load "./example4.lisp")

(defun quarter-turn (arr)
  (let ((dim (array-dimensions arr)))
	(let ((d1 (first dim))
		  (d2 (second dim))
		  (new (make-array (reverse dim))))
	  (do ((i 0 (+ i 1)))
		  ((= i d1))
		(do ((j 0 (+ j 1)))
			((= j d2))
		  (setf (aref new j (- (- d1  1) i))
				(aref arr i j))))
	  new)))

;; 2. use function 'reduce' to define (a) copy-list (b) reverse (for list)

;; (defun my-copy-list (lst)
;;   (let ((first nil))
;; 	(reduce #'(lambda (x y)
;; 				(if (null first)
;; 					(progn
;; 					  (setf first t)
;; 					  (cons x (cons y nil)))
;; 					(append x (cons y nil))))
;; 			lst)))

;; (defun my-reverse (lst)
;;   (let ((first nil))
;;    (reduce #'(lambda (x y)
;; 			   (if (null first)
;; 				   (progn
;; 					 (setf first t)
;; 					 (cons y (cons x nil)))
;; 				   (cons y x)))
;; 		   lst)))

(defun my-copy-list (lst)
  (reduce #'cons lst :from-end t
		  :initial-value nil))
(defun my-reverse (lst)
  (reduce #'(lambda(x y)
			  (cons y x))
		  lst :initial-value nil))

(defstruct tnode
  (elt nil)
  (key nil)
  (value nil)
  (left nil)
  (mid nil)
  (right nil))

(defun my-copy-tree (tree)
  (if (null tree)
	  nil
	  (make-tnode :elt (tnode-elt tree)
				 :key (tnode-key tree)
				 :value (tnode-value tree)
				 :left (copy-tree (tnode-left tree))
				 :mid (copy-tree (tnode-mid tree))
				 :right(copy-tree (tnode-right tree)))))

(defun find-tree (data tree)
  (if (null tree)
	  nil
	  (or (or (eql (tnode-elt tree) data)
			  (eql (tnode-key tree) data)
			  (eql (tnode-value tree) data))
		  (find-tree data (tnode-left tree))
		  (find-tree data (tnode-mid tree))
		  (find-tree data (tnode-right tree)))))


(defun bst-list (bst)
  (if (null bst)
	  nil
	  (append (bst-list (node-r bst))
			  (cons (node-elt bst) nil)
			  (bst-list (node-l bst)))))

(defun bst-adjoin (obj bst <)
  (if (null bst)
	  (make-node :elt obj)
	  (let ((elt (node-elt bst)))
		(cond ((eql elt obj)
			   (make-node :elt elt
						  :l (node-l bst)
						  :r (node-r bst)))
			   ((if (funcall < obj elt)
					(make-node :elt elt
						  :l (bst-adjoin obj (node-l bst) <)
						  :r (node-r bst))))
			   (t (make-node :elt elt
							 :r (bst-adjoin obj (node-r bst) <)
							 :l (node-l bst)))))))

(defun asslst-hash (ass)
  (let((ht (make-hash-table))) 
	(dolist (x ass)
	  (push (cdr x) (gethash (car x) ht)))
	ht))

(defun hash-asslst (hash)
  (let ((ass nil))
	(maphash #'(lambda (k v)
				 (dolist (x v)
				   (push (cons k x) ass))) hash)
	ass))
