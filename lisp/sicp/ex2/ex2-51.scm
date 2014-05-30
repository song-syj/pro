;; Exercise 2.51: Define the below operations for painters.
;; Below takes tow painters as arguments. The resulting painter,
;; given a frame, draw with the first pianter in the bottom of
;; the frame and with the second painter in the top . Define below
;; int two different ways -first by writing a prcoedure that is analogous
;; to the beside procedure given above, and again in terms of beside
;;  and suitable rotaiton operations (from Exercise 2.50)

(define (below2 painter1 painter2)
  (let ((split-point (make-vect 0.0 0.5)))
	(let ((painter-top (transform-painter2 painter2
										   split-point
										   (make-vect 1.0 0.5)
										   (make-vect 0.0 1.0)))
		  (painter-bottom (transform-painter2 painter1
											  (make-vect 0.0 0.0)
											  (make-vect 1.0 0.0)
											  split-point)))
	  (lambda (frame)
		(painter-top frame)
		(painter-bottom frame)))))

(define (below2 painter1 painter2)
  (rotate90_ (beside2 (rotate270_ painter2)
 					  (rotate270_ painter1))))


