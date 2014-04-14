;; 1

((lambda (x) (cons x x)) (car y))

((lambda (w)
   ((lambda (y) (cons w y)) (+ w z))) (car x))

;; 2

(defun mystery (x y)
  (cond ((null y)
		 nil)
		((eql (car y) x)
		 0)
		(t (let ((z (mystery x (cdr y))))
			 (and z (+ z 1))))))
;; 3
(defun sq (x)
  (if (and (integerp x)
		   (< 0 x 6))
	  x
	  (* x x)))

;; 4
(defun month-num (m y)
 (+ (svref month (- m 1))
	(if (leap? y)
		(case m
		  ((1 2) 0)
		  ((3 4 5 6 7 8 9 10 11 12) 1))
		0)))
		  
;; 5
(defun precedes-recur (x v)
  (let ((len (length v)))
	(cond ((< len 2)
		   nil)
		  ((eql x (aref v 1))
		   (adjoin (aref v 0) (precedes-recur x (subseq v 1))))
		  (t (precedes-recur x (subseq v 1))))))

(defun precedes-iter (x v)
  (let ((l (length v))
		(prec nil))
	(if (< l 2)
		nil
		(dotimes (i (- l 1) prec)
		  (when (eql x (aref v (+ i 1)))
			(setf prec (adjoin (aref v i) prec)))))))

(defun presedes (x v)
  (let (acc (v1 (concatenate 'vector v)))
    (dotimes (i (length v1))
      (if (and (eql x (svref v1 i)) (< 0 i))
	  (push (svref v1 (- i 1)) acc)))
    (remove-duplicates acc)))

;; 6

(defun intersperse-recur (obj lst)
  (if (<= (length lst) 1)
	  lst
	  (append (list (car lst) obj) (intersperse obj (cdr lst)))))

(defun intersperse-iter (obj lst)
  (let ((new nil))
	(dolist (elt lst (reverse new))
	  (if new
		  (push obj new))
	  (push elt new))))

;; 7

(defun diff-pair-cur (lst diff)
  (and lst (cdr lst)
	   (= diff (- (cadr lst) (car lst)))
	   (if (cddr lst)
		   (diff-pair-cur (cddr lst) diff)
		   t)))

(defun diff-pair-do (lst diff)
  (let ((len (length lst)))
	(and lst (evenp len)
		 (do ((l lst (cddr l)))
			 ((or (null l)
				  (/= diff (- (cadr l) (car l))))
			  (null l))))))

(defun diff-pair-mapc (lst diff)
  (block nil
	(and lst
		 (let ((fir nil))
		   (mapc #'(lambda (x)
					 (if (null fir)
						 (setf fir x)
						 (if (/= diff (- x fir))
							 (return nil)
						   (setf fir nil)))) lst)
		   (null fir)))))

;; 8

(defun vector-max-min (vec)
  (let ((head (svref vec 0)))
	(if (= 1 (length vec))
		(values head head)
		(multiple-value-bind (max min)
			(vector-max-min (subseq vec 1))
		  (values (max max head) (min min head))))))

(defun vector-max-min (vec)
  (vector-max-min-recur vec 0 (- (length vec) 1)))

(defun vector-max-min-recur (vec head tail)
  (cond ((< (- tail head) 0)
		 nil)
		((zerop (- tail head))
		 (values (svref vec head) (svref vec tail)))
		(t (multiple-value-bind (max min)
			   (vector-max-min-recur vec (+ head 1) tail)
			 (values (max max (svref vec head))
					 (min min (svref vec head)))))))
