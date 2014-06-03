;; Example: Representing Sets

(defun element-of-set? (x set)
  (cond ((null set) nil)
		((equal x (car set)) t)
		(t (element-of-set? x (cdr set)))))

(defun adjoin-set (x set)
  (if (element-of-set? x set)
	  set
	  (cons x set)))

(defun intersection-set (set1 set2)
  (cond ((or (null set1) (null set2)) nil)
		((element-of-set? (car set1) set2)
		 (cons (car set1)
			   (intersection-set (cdr set1) set2)))
		(t (intersection-set (cdr set1) set2))))
(do ((i 1 (+ i 1))
	 (set nil (adjoin-set i set)))
	((> i 10) set))
