;; Example: Representing Sets
;;; unsorted list presentation of sets

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

(defun union-set (set1 set2)
  (cond ((null set1) set2)
		((null set2) set1)
		(t (union-set  (cdr set1)
					   (adjoin-set (car set1) set2)))))

(setf x  (do ((i 1 (+ i 1))
			  (set nil (adjoin-set i set)))
			 ((> i 10) set)))

(setf y  (do ((i 5 (+ i 1))
			  (set nil (adjoin-set i set)))
			 ((> i 17) set)))

;; set as a sorted list

(defun element-of-set? (x set)
  (cond ((null set) nil)
		((= x (car set)) t)
		((< x (car set)) nil)
		(t (element-of-set? x (cdr set)))))

(defun intersection-set (set1 set2)
  (if (or (null set1) (null set2))
	  nil
	  (let ((x1 (car set1))
			(x2 (car set2)))
		(cond ((= x1 x2)
			   (cons x1 (intersection-set (cdr set1)
										  (cdr set2))))
			  ((< x1 x2)
			   (intersection-set (cdr set1) set2))
			  (t (intersection-set set1 (cdr set2)))))))

(defun adjoin-set (x set)
  (cond ((null set) (cons x set))
		((= x (car set)) set)
		((< x (car set)) (cons x set))
		(t (cons (car set) (adjoin-set x (cdr set))))))

(defun union-set (set1 set2)
  (if (or (null set1) (null set2))
	  (append set1 set2)
	  (let ((x1 (car set1))
			(x2 (car set2)))
		(cond ((= x1 x2) (cons x1 (union-set (cdr set1) (cdr set2))))
			  ((< x1 x2) (cons x1 (union-set (cdr set1) set2)))
			  (t (cons x2 (union-set set1 (cdr set2))))))))
