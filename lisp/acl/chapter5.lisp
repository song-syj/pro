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
(defun precedes (x v)
  ())
