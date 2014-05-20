;; Exercise 2.2: Consider the problem of representing line
;; segments in a plane. Each segment is represented as a pair
;; of points: a starting point and an ending point. Deﬁne a
;; constructor make-segment and selectors start-segment and
;; end-segment that deﬁne the representation of segments in
;; terms of points. Furthermore, a point can be represented
;; as a pair of numbers: the x coordinate and the y coordi-
;; nate. Accordingly, specify a constructor make-point and
;; selectors x-point and y-point that deﬁne this representa-
;; tion. Finally, using your selectors and constructors, deﬁne a
;; procedure midpoint-segment that takes a line segment as
;; argument and returns its midpoint (the point whose coor-
;; dinates are the average of the coordinates of the endpoints).
;; To try your procedures, you’ll need a way to print points:
;; (define (print-point p)
;; 	(newline)
;;   (display "(")
;;   (display (x-point p))
;;   (display ",")
;;   (display (y-point p))
;;   (display ")"))

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
