;; Exercise 2.12: Deﬁne a constructor make-center-percent
;; that takes a center and a percentage tolerance and pro-
;; duces the desired interval. You must also deﬁne a selector
;; percent that produces the percentage tolerance for a given
;; interval. The center selector is the same as the one shown
;; above.

(defun make-center-width (c w)
  (make-interval (- c w) (+ c w)))

(defun center-interval (i)
  (/ (+ (upper-bound i) (lower-bound i)) 2.0))

(defun width-interval (x)
  (/ (- (upper-bound x) (lower-bound x)) 2.0))

(defun make-center-percent (c p)
  (make-center-width c (* c p 0.01)))

(defun percent-interval (x)
  (* 100 (/ (width-interval x) (center-interval x))))
