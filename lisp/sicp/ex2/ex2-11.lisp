;; Exercise 2.11: In passing, Ben also cryptically comments:
;; “By testing the signs of the endpoints of the intervals, it is
;; possible to break mul-interval into nine cases, only one
;; of which requires more than two multiplications.” Rewrite
;; this procedure using Ben’s suggestion.

(defun mul-interval (x y)
  (let ((xl (lower-bound x))
		(xu (upper-bound x))
		(yl (lower-bound y))
		(yu (upper-bound y)))
	(cond ((and (> xl 0) (> yl 0))
		   (make-interval (* xl yl)
						  (* xu yu)))
		  ((and (< xu 0) (< yu 0))
		   (make-interval (* xu yu) (* xl yl)))
		  ((and (< xu 0) (> yl 0))
		   (make-interval (* xl yu) (* xu yl)))
		  ((and (< yu 0) (> xl 0))
		   (make-interval (* xu yl) (* xl yu)))
		  ((and (> xl 0) (> yu 0))
		   (make-interval (* yl xu) (* yu xu)))
		  ((and (> yl 0) (> xu 0))
		   (make-interval (* yu xl) (* yu xu)))
		  ((and (< xu 0) (> yu 0))
		   (make-interval (* xl yu) (* xl yl)))
		  ((and (< yu 0) (> xu 0))
		   (make-interval (* yl xu) ( * yl xl)))
		  (t   (let ((p1 (* xl yl))
					 (p2 (* xu yu))
					 (p3 (* xl yu))
					 (p4 (* xu yl)))
				 (make-interval (min p1 p2 p3 p4)
								(max p1 p2 p3 p4)))))))

