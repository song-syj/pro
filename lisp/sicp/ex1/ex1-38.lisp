;; Exercise 1.38: In 1737, the Swiss mathematician Leonhard
;; Euler published a memoir De Fractionibus Continuis, which
;; included a continued fraction expansion for e − 2, where
;; e is the base of the natural logarithms. In this fraction, the
;; Ni are all 1, and the Di are successively 1, 2, 1, 1, 4, 1, 1,
;; 6, 1, 1, 8, . . .. Write a program that uses your cont-frac
;; procedure from Exercise 1.37 to approximate e, based on
;; Euler’s expansion.

(defun cont-frac-iter (n d k)
  (labels ((frac-item (n d k value)
			 (/ (funcall n k) (+ (funcall d k) value)))
		   (frac-iter (n d k v)
			 (if (= k 0)
				 v
				 (frac-iter n d (- k 1) (frac-item n d k v)))))
	(frac-iter n d k 0.0d0)))

(defun d-i (i)
  (if (= (mod i 3) 2)
	  (+ 2.0d0 (* 2 (truncate (/ i 3))))
	  1.0d0))
(defun n-i (i)
  1)

(cont-frac-iter #'n-i #'d-i 10)



(do ((i 1 (+ i 1)))
	((> i 20))
  (print (d-i i)))

