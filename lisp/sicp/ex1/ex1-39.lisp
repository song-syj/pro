;; Exercise 1.39: A continued fraction representation of the
;; tangent function was published in 1770 by the German math-
;; ematician J.H. Lambert:
;; where x is in radians. Define a procedure (tan-cf x k) that
;; computes an approximation to the tangent function based
;; on Lambert’s formula. k specifies the number of terms to
;; compute, as in Exercise 1.37.

(defun cont-frac-iter (n d k)
  (labels ((frac-item (n d k value)
			 (/ (funcall n k) (+ (funcall d k) value)))
		   (frac-iter (n d k v)
			 (if (= k 0)
				 v
				 (frac-iter n d (- k 1) (frac-item n d k v)))))
	(frac-iter n d k 0.0d0)))

(defun tan-cf (x k)
  (labels ((d (i) (- (* 2 i) 1))
		   (n (i) (if (= i 1)
					  x
					  (- (* x x)))))
	(cont-frac-iter #'n #'d k)))
