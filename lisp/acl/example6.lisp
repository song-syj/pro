;; 6-1
(defun single? (lst)
  (and (consp lst) (null (cdr lst))))

(defun append1 (lst obj)
  (append lst (list obj)))

(defun map-int (fn n)
  (let ((acc nil))
	(dotimes (i n)
	  (push (funcall fn i) acc))
	(nreverse acc)))

(defun filter (fn lst)
  (let ((acc nil))
	(dolist (x lst)
	  (let ((val (funcall fn x)))
		(if val (push val acc))))
	(nreverse acc)))

(defun most (fn lst)
  (if (null lst)
	  (values nil nil)
	  (let* ((wins (car lst))
			 (max (funcall fn wins)))
		(dolist (obj (cdr lst))
		  (let ((score (funcall fn obj)))
			(when (> score max)
			  (setf wins obj
					max score))))
		(values wins max))))

;; 6-2
(defun compose (&rest fns)
  (destructuring-bind (fn1 . rest) (reverse fns)
	#'(lambda (&rest args)
		(reduce #'(lambda (v f) (funcall f v))
				rest
				:initial-value (apply fn1 args)))))

(defun disjoin (fn &rest fns)
  (if (null fns)
	  fn
	  (let ((disj (apply #'disjoin fns)))
		#'(lambda (&rest args)
			(or (apply fn args) (apply disj args))))))

(defun conjoin (fn &rest fns)
  (if (null fns)
	  fn
	  (let ((conj (apply #'conjoin fns)))
		#'(lambda (&rest args)
			(and (apply fn args) (apply conj args))))))

(defun curry (fn &rest args)
  #'(lambda (&rest args2)
	  (apply fn (append args args2))))

(defun rcurry (fn &rest args)
  #'(lambda (&rest args2)
	  (apply fn (append args2 args))))

(defun always (x) #'(lambda (&rest args) x))

(defun our-mapcan (fn &rest args)
  (funcall (compose (curry #'apply #'nconc) #'mapcar) fn args))
