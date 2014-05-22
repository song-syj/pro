;; Exercise 2.10: Ben Bitdiddle, an expert systems program-
;; mer, looks over Alyssa’s shoulder and comments that it is
;; not clear what it means to divide by an interval that spans
;; zero. Modify Alyssa’s code to check for this condition and
;; to signal an error if it occurs.

(defun div-interval (x y)
  (let ((upy (upper-bound y))
		(lowy (lower-bound y)))
	(if (and (>= upy 0) (<= lowy 0))
		(error "the divided interval spans zero!")
		(mul-interval x (make-interval (/ 1.0 upy)
									   (/ 1.0 lowy))))))

