;; Example: Arithmetic Operations for Rational Numbers

(defun make-rat (n d)
  (let ((g (funcall (if (< d 0) #'- #'+) (gcd n d))))
	(if (= d 0)
		(error " Denom can't be zero!")
		(cons (/ n g) (/ d g)))))

(defun numer (x) (car x))
(defun denom (x) (cdr x))
(defun print-rat (x)
  (let ((n (numer x))
		(d (denom x)))
  (cond ((zerop n) (format t "0~%"))
		((= d 1) (format t "~A~%" n))
		(t (format t "~A/~A~%" n d)))))

;; 2.1.4 Extended Exercise: Interval Arithmetic
(defun add-interval (x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
				 (+ (upper-bound x) (upper-bound y))))

(defun mul-interval (x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
		(p2 (* (lower-bound x) (upper-bound y)))
		(p3 (* (upper-bound x) (upper-bound y)))
		(p4 (* (upper-bound x) (lower-bound y))))
	(make-interval (min p1 p2 p3 p4)
				   (max p1 p2 p3 p4))))

(defun div-interval (x y)
  (mul-interval x (make-interval (/ 1.0 (upper-bound y))
								 (/ 1.0 (lower-bound y)))))


