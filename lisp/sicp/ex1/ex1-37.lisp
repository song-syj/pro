;; Check your procedure by approximating 1/φ using 
;; (cont-frac (lambda (i) 1.0)
;; 		   (lambda (i) 1.0)
;; 		   k)
;; for successive values of k. How large must you make
;; k in order to get an approximation that is accurate to
;; 4 decimal places?

(defun cont-frac-rec (n d k)
  (labels ((frac-item (n d k value)
			 (/ (funcall n k) (+ (funcall d k) value)))
		   (frac-rec (n d i)
			 (if (> i k)
				 0
				 (frac-item n d i (frac-rec n d (+ i 1))))))
	(frac-rec n d 1)))

(defun cont-frac-iter (n d k)
  (labels ((frac-item (n d k value)
			 (/ (funcall n k) (+ (funcall d k) value)))
		   (frac-iter (n d k v)
			 (if (= k 0)
				 v
				 (frac-iter n d (- k 1) (frac-item n d k v)))))
	(frac-iter n d k 0)))

(defun find-min-k (n d answer tolerance)
  (labels ((close-enough? (guess)
			 (< (abs (- guess answer)) tolerance))
		   (iter-find (k)
			 (print k)
			 (if (close-enough? (cont-frac-iter n d k))
				 k
				 (iter-find (+ k 1.0)))))
	(iter-find 1)))

(setf theta (/ 1 (/ (+ (sqrt 5) 1) 2)))
(find-min-k #'(lambda (i) 1.0d0) #'(lambda (i) 1.0d0) theta 0.0001)
