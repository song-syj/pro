#lang racket

(require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))

(define painter einstein)

(define (flipped-pairs painter)
  (let ((painter2 (beside painter (flip-vert painter))))
	(below painter2 painter2)))

(define (right-split painter n)
  (if (= n 0)
	  painter
	  (let ((smaller (right-split painter (- n 1))))
		(beside painter (below smaller smaller)))))

(define (up-split painter n)
  (if (= n 0)
	  painter
	  (let ((smaller (up-split painter (- n 1))))
		(below painter (beside smaller smaller)))))

(define (corner-split painter n)
  (if (= n 0)
	  painter
	  (let ((up (up-split painter (- n 1)))
			(right (right-split painter (- n 1))))
		(let ((top-letf (beside up up))
			  (bottom-right (below right right)))
		  (beside (below painter top-letf)
				  (below bottom-right (corner-split painter (- n 1))))))))

(define (square-limit painter n)
  (let ((quarter (corner-split painter n)))
	(let ((half (beside (flip-horiz quarter) quarter)))
	  (below (flip-vert half) half))))

(define (square-of-four tl tr bl br)
  (lambda (painter)
	(let ((top (beside (tl painter) (tr painter)))
		  (bottom (beside (bl painter) (br painter))))
	  (below bottom top))))

;; (define (flipped-pairs painter)
;;   (let ((combine4 (square-of-four identity flip-vert
;; 								  identity flip-vert)))
;; 	(combine4 painter)))

;; (define (square-limit painter n)
;;   (let ((combine4 (square-of-four flip-horiz identity rotate180 flip-vert)))
;; 	(combine4 (corner-split painter n))))

;; (define (frame-coord-map frame)
;;   (lambda (v)
;; 	(add-vect (origin-frame frame)
;; 			  (add-vect (scale-vect (xcor-vect v)
;; 									(edge1-frame frame))
;; 						(scale-vect (ycor-vect v)
;; 									(edge2-frame frame))))))

;; (define (segments->painter segment-list)
;;   (lambda (frame)
;; 	(for-each
;; 	 (lambda (segment)
;; 	   (draw-line ((frame-coord-map frame) (start-segment segment))
;; 				  ((frame-coord-map frame) (end-segment segment))))
;; 	 segment-list)))

;; (define (make-vect x y)
;;   (cons x y))

(define (xcor-vect v)
		 (car v))

(define (ycor-vect v)
  (cdr v))

(define (add-vect v1 v2)
  (make-vect (+ (xcor-vect v1) (xcor-vect v2))
			 (+ (ycor-vect v1) (ycor-vect v2))))

(define (sub-vect v1 v2)
  (make-vect (- (xcor-vect v1) (xcor-vect v2))
			 (- (ycor-vect v1) (ycor-vect v2))))

(define (scale-vect  s v)
  (make-vect (* (xcor-vect v) s)
			 (* (ycor-vect v) s)))


(define (transform-painter2 painter origin corner1 corner2)
  (lambda (frame)
	(let ((m (frame-coord-map frame)))
	  (let ((new-origin (m origin)))
		(painter
		 (make-frame new-origin
					 (sub-vect (m corner1) new-origin)
					 (sub-vect (m corner2) new-origin)))))))

(define (flip-vert2 painter)
  (transform-painter2 painter
					 (make-vect 0 1.0)
					 (make-vect 1.0 1.0)
					 (make-vect 0 0)))

(define (shrink-to-upper-right painter)
  (transform-painter2 painter
					 (make-vect 0.5 0.5)
					 (make-vect 1.0 0.5)
					 (make-vect 0.5 1.0)))

(define (squash-inwards painter)
  (transform-painter2 painter
					  (make-vect 0.0 0.0)
					  (make-vect 0.4 0.3)
					  (make-vect 0.3 0.4)))

(define (two-sub painter)
  (lambda (frame)
	((transform-painter2 painter
						 (make-vect 0 0)
						 (make-vect 0.5 0)
						 (make-vect 0 0.5))
	 frame)
	((transform-painter2 painter
						 (make-vect 0.5 0.5)
						 (make-vect 1.0 0.5)
						 (make-vect 0.5 1.0))
	 frame)))

(define (beside2 painter1 painter2)
  (let ((split-point (make-vect 0.5 0.0)))
	(let ((painter-left (transform-painter2 painter1
											(make-vect 0.0 0.0)
											split-point
											(make-vect 0.0 1.0)))
		  (painter-right (transform-painter2 painter2
											split-point
											(make-vect 1.0 0.0)
											(make-vect 0.5 1.0))))
	  (lambda (frame)
		(painter-left frame)
		(painter-right frame)))))

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

(define (rotate90_ painter)
    (transform-painter2 painter
					  (make-vect 1.0 0.0)
					  (make-vect 1.0 1.0)
					  (make-vect 0.0 0.0)))


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

;; (define (below2 painter1 painter2)
;;   (rotate90_ (beside2 (rotate270_ painter2)
;; 					 (rotate270_ painter1))))

