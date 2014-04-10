;;2. Write a version of union that preserves the order of the elements in
;;the original lists

(defun new-union (list1 list2)
  (let ((tmp (reverse list1)))
	(dolist (x list2)
	  (if (not (member x tmp))
		  (push x tmp)))
	(reverse tmp)))

;;3. Define a function that takes a list and returns a list indicating the
;;number of times each (eql) element appears, sorted from most common
;;element to least common

(defun occurrences (lst)
  (let ((sat nil))
	(dolist (x lst)
	  (let ((p (assoc x sat)))
		(if p	
			(incf (cdr p))
			(push (cons x 1) sat))))
	(sort sat #'> :key #'cdr)))

;;4. Suppose the function pos+ takes a list and returns a list of each element
;; plus its position

#|(defun pos+ (lst)
  (let ((n 0)
		(new nil))
	(dolist (x lst)
	  (push (+ x n) new)
	  (incf n))
	(reverse new))) |#

(defun pos+ (lst)
  (let ((i -1))
	(mapcar #'(lambda (x) (incf i) (+ x i)) lst)))

;;6. After years of deliberation, a government commission has decided that
;;lists should be represented by using the cdr to point to the first element
;;and the car to point to the rest of the list. Define the government
;;versions of the following functions

;;(a)
#|(defun cons (x y)
  (let ((node (nil .nil)))
	(setf (cdr node) x
		  (car node) y)
	node))

;;(b)
(defun list (&rest arg)
  arg)

;;(c)
(defun length (lst)
  (if (null lst)
	  0
	  (+ 1 (length (car lst)))))

;;(d)
(defun member (x lst)
  (if (null lst)
	  nil
	  (if (eql x (cdr lst))
		  lst
		  (member x (car lst))))) |#

;; 7.
(defun compress (x)
  (if (consp x)
	  (compr (car x) 1 (cdr x))
	  x))
(defun compr (elt n lst)
  (if (null lst)
	  (list (n-elts elt n))
	  (let ((next (car lst)))
		(if (eql next elt)
			(compr elt (+ n 1) (cdr lst))
			(cons (n-elts elt n)
				  (compr next 1(cdr lst)))))))
(defun n-elts (elt n)
  (if (> n 1)
	  (cons n elt)
	  elt))

;;8.
(defun showdots (lst)
  (if (atom lst)
	  (format t "~A" lst)
	  (progn
		(format t "(")
		(showdots (car lst))
		(format t " . ")
		(showdots (cdr lst))
		(format t ")"))))

;;9.
#|(defun longest-path (start end net)
  (bfs end nil (list (list start)) net))

(defun bfs (end opt queue net)
  (if (null queue)
	  (reverse opt)
	  (let ((path (car queue)))
		(let ((node (car path)))
		  (if (null node)
			  (bfs end opt (cdr queue) net)
			  (if (eql node end)
				  (bfs end path (cdr queue) net)
				  (bfs end
					   opt
					   (append (cdr queue)
							   (new-paths path node net))
					   net)))))))

(defun new-paths (path node net)
  (mapcar #'(lambda (x)
			  (if (not (member x path))
				  (adjoin x path)))
		  (cdr (assoc node net))))

#|(defun new-paths (path node net)
  (let ((lst (cdr (assoc node net)))
		(new nil))
	(dolist (x lst)
	  (or (member x path)
		  (push (cons x path) new)))
	new)) |#
|#
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;; another method ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(defun new-paths (path node net)
  (let (acc)
    (dolist (x (cdr (assoc node net)))
      (or (member x path)
          (push (cons x path) acc)))
    acc))

(defun bfs-l (end queue net sol)
  (if  queue
	   (let ((path (car queue)))
		 (let ((node (car path)))
		   (bfs-l  end
				   (append (cdr queue) (new-paths path node net))
				   net
				   (if (eql node end)  path sol))))
	   (reverse sol)))

(defun longest-path (start end net)
  (bfs-l end (list (list start)) net nil))
  
