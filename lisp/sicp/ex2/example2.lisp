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
(defun sub-interval (x y)
  (make-interval (- (lower-bound x) (upper-bound y))
				 (- (upper-bound x) (lower-bound y))))

(defun make-interval (a b) (cons a b))
(defun upper-bound (x) (cdr x))
(defun lower-bound (x) (car x))

(defun width-interval (x)
  (/ (- (upper-bound x) (lower-bound x)) 2.0))

(defun div-interval (x y)
  (let ((upy (upper-bound y))
		(lowy (lower-bound y)))
	(if (and (>= upy 0) (<= lowy 0))
		(error "the divided interval spans zero!")
		(mul-interval x (make-interval (/ 1.0 upy)
									   (/ 1.0 lowy))))))

(defun make-center-width (c w)
  (make-interval (- c w) (+ c w)))

(defun center-interval (i)
  (/ (+ (upper-bound i) (lower-bound i)) 2.0))

(defun width-interval (x)
  (/ (- (upper-bound x) (lower-bound x)) 2.0))

;;Sequences as Conventional Interfaces

(defun filter (predicate sequence)
  (cond ((null sequence) nil)
		((funcall predicate (car sequence))
		 (cons (car sequence)
			   (filter predicate (cdr sequence))))
		(t (filter predicate (cdr sequence)))))

(defun accumulate (op initial sequence)
  (if (null sequence)
	  initial
	 (funcall op (car sequence)
				  (accumulate op initial (cdr sequence)))))

(defun enumerate-interval (low high)
  (if (> low high)
	  nil
	  (cons low (enumerate-interval (+ low 1)  high))))

(defun enumerate-tree (tree)
  (cond ((null tree) nil) 
		((atom tree) (list tree))
		(t (append (enumerate-tree (car tree))
				   (enumerate-tree (cdr tree))))))

(defun sum-odd-squares (tree)
  (accumulate
   #'+ 0 (mapcar #'square (filter #'oddp (enumerate-tree tree)))))

(defun fib (n)
  (if (<= n 1) 
	  n
	  (+ (fib (- n 1))
		 (fib (- n 2)))))

(defun even-fibs (n)
  (accumulate
   #'cons nil (filter #'evenp (mapcar #'fib (enumerate-interval 0 n)))))

(defun square (x)
  (* x x))

(defun list-fib-squares (n)
  (accumulate #'cons nil
			  (mapcar #'square
					  (mapcar #'fib
							  (enumerate-interval 0 n)))))

(defun product-of-square-of-odd-elements (sequence)
  (accumulate #'* 1
			  (mapcar #'square
					  (filter #'oddp sequence))))

;; (defun salary-of-highest-paid-programmer (records)
;;   (accumulate #'max 0 (mapcar #'salary (filter #'programmer? records))))

;; Nested Mapping

(defun flatmap (proc seq)
  (accumulate #'append nil (mapcar proc seq)))

(defun prime-sum? (pair)
  (prime? (+ (car pair) (cadr pair))))

(defun make-pair-sum (pair)
  (list (car pair) (cadr pair) (+ (car pair) (cadr pair))))

(defun prime-pair-sum (n)
  (mapcar #'make-pair-sum
		  (filter #'prime-sum?
				  (flatmap #'(lambda (i)
							   (mapcar #'(lambda (j)
										   (list j i))
									   (enumerate-interval 1 (- i 1))))
						   (enumerate-interval 1 n)))))

(defun permutations (s)
  (if (null s)
	  (list nil)
	  (flatmap #'(lambda (x)
				   (mapcar #'(lambda (p)
							   (cons x p))
						   (permutations (remove x s))))
	   s)))


