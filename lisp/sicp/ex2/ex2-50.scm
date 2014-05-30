;; Exercise 2.50: Deﬁne the transformation flip-horiz , which
;; ﬂips painters horizontally, and transformations that rotate
;; painters counterclockwise by 180 degrees and 270 degrees.

(define (flip-horiz2 painter)
  (transform-painter2 painter
					  (make-vect 1.0 0.0)
					  (make-vect 0.0 0.0)
					  (make-vect 1.0 1.0)))

(define (rotate270_ painter)
    (transform-painter2 painter
					  (make-vect 0.0 1.0)
					  (make-vect 0.0 0.0)
					  (make-vect 1.0 1.0)))

(define (rotate180_ painter)
    (transform-painter2 painter
					  (make-vect 1.0 1.0)
					  (make-vect 0.0 1.0)
					  (make-vect 1.0 0.0)))

