(defun sum (term a next b)
  (if (> a b)
	  0
	  (+ (funcall term a)
		 (sum term (funcall next a) next b))))

(defun inc (n) (+ n 1))
(defun cube (x)
  (* x x x))
(defun sum-cubes (a b)
  (sum #'cube a #'inc b))

(defun sum-integers (a b)
  (sum #'identity a #'inc b))

(defun pi-sum (a b)
  (labels ((pi-term (x)
			 (/ 1.0 (* x (+ x 2))))
		   (pi-next (x)
			 (+ x 4)))
	(sum #'pi-term a #'pi-next b)))

(defun integral (f a b dx)
  (* (sum f
		  (+ a (/ dx 2.0))
		  #'(lambda (x) (+ x dx))
		  b)
	 dx))
