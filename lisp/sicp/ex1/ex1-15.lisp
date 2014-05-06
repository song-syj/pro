;; Exercise 1.15: The sine of an angle (speciﬁed in radians)
;; can be computed by making use of the approximation sin x ~= x
;; if x is suﬃciently small, and the trigonometric identity
;; sin(x) = 3sin(x/3) - 4sin(x/3)^3
;; to reduce the size of the argument of sin. (For purposes of
;; this exercise an angle is considered “suﬃciently small” if its
;; magnitude is not greater than 0.1 radians.) ese ideas are
;; incorporated in the following procedures:
(defun cube (x) (* x x x))
(defun p (x) (- (* 3 x) (* 4 (cube x))))
(defun sine (angle)
  (if (not (> (abs angle) 0.1))
	  angle
	  (p (sine (/ angle 3.0)))))
;; a. How many times is the procedure p applied when (sine
;; 12.15) is evaluated?
;; b. What is the order of growth in space and number of
;; steps (as a function ofa) used by the process generated
;; by the sine procedure when (sine a) is evaluated?
