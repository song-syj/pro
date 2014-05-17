;; Exercise 1.35: Show that the golden ratio φ (Section 1.2.2)
;; is a fixed point of the transformation x → 1 + 1/x , and
;; use this fact to compute φ by means of the fixed-point
;; procedure.
(defun fixed-point (f first-guess)
  (labels ((close-enough? (v1 v2)
		   (< (abs (- v1 v2)) 1e-16))
		   (try (guess)
			 (let ((next (funcall f guess)))
			   (if (close-enough? next guess)
				   next
				   (try next)))))
	(try first-guess)))

(fixed-point #'(lambda (x) (+ 1 (/ 1.0d0 x))) 1.0d0)
