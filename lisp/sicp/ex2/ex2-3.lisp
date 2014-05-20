;; Exercise 2.3: Implement a representation for rectangles in
;; a plane. (Hint: You may want to make use of Exercise 2.2.) In
;; terms of your constructors and selectors, create procedures
;; that compute the perimeter and the area of a given rectan-
;; gle. Now implement a diﬀerent representation for rectan-
;; gles. Can you design your system with suitable abstraction
;; barriers, so that the same perimeter and area procedures
;; will work using either representation?

;; To simplify things, we'll assume that the sides of the rectangle are to be perpendicular to the x- and y-axes of the coordinate plane.

(defun make-segment (p1 p2)
  (cons p1 p2))

(defun start-segment (seg)
  (car seg))

(defun end-segment (seg)
  (cdr seg))

(defun make-point (x y)
  (cons x y))

(defun x-point (p)
  (car p))

(defun y-point (p)
  (cdr p))

(defun print-point (p)
  (format t "(~A, ~A)~%" (x-point p) (y-point p)))

(defun midpoint-segment (seg)
  (make-point (average (x-point (start-segment seg))
					   (x-point (end-segment seg)))
			  (average (y-point (start-segment seg))
					   (y-point (end-segment seg)))))

(defun average (x y)
  (/ (+ x y) 2))


(defun make-rect (bottom-left top-right)
  (cons bottom-left top-right))

(defun bottom-left-rect (rect)
  (car rect))

(defun top-right-rect (rect)
  (cdr rect))

(defun bootom-right-rect (rect)
  (make-point (x-point (top-right-rect rect))
			  (y-point (bottom-left-rect rect))))

(defun top-left-rect (rect)
  (make-point (x-point (bottom-left-rect rect))
			  (y-point (top-right-rect rect))))

(defun width-rect (rect)
  (abs (- (y-point (top-left-rect rect))
		  (y-point (bottom-left-rect rect)))))

(defun length-rect (rect)
  (abs (- (x-point (bootom-right-rect rect))
		  (x-point (bottom-left-rect rect)))))

(defun  area-rect (rect)
  (* (length-rect rect)
	 (width-rect rect)))

(defun perimeter-rect (rect)
  (* 2 (+ (length-rect rect)
		  (width-rect rect))))

;; the second impelementation

(defun make-rect2 (origin-point x-seg y-seg)
  (list origin-point x-seg y-seg))

(defun square (x)
  (* x x))

(defun x-seg-rect (rect)
  (cadr rect))

(defun y-seg-rect (rect)
  (caddr rect))

(defun length-segment (seg)
  (sqrt (+ (square (- (x-point (start-segment seg))
					  (x-point (end-segment seg))))
		   (square (- (y-point (start-segment seg))
					  (y-point (end-segment seg)))))))

(defun length-rect (rect)
  (length-segment (x-seg-rect rect)))

(defun width-rect (rect)
  (length-segment (y-seg-rect rect)))

(defun  area-rect (rect)
  (* (length-rect rect)
	 (width-rect rect)))

(defun perimeter-rect (rect)
  (* 2 (+ (length-rect rect)
		  (width-rect rect))))

