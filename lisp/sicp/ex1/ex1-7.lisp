;; Exercise 1.7: The good-enough? test used in computing
;; square roots will not be very effective for finding the square
;; roots of very small numbers. Also, in real computers, arithmetic
;; operations are almost always performed with limited
;; precision. This makes our test inadequate for very large
;; numbers. Explain these statements, with examples showing
;; how the test fails for small and large numbers. An alternative
;; strategy for implementing good-enough? is to watch
;; how guess changes from one iteration to the next and to
;; stop when the change is a very small fraction of the guess.
;; Design a square-root procedure that uses this kind of end
;; test. Does this work better for small and large numbers?

(defun sqrt-iter (guess x)
  (if (good-enough? guess x)
	  guess
	  (sqrt-iter (improve guess x)
				 x)))

(defun improve (guess x)
  (average guess (/ x guess)))

(defun average (x y)
  (/ (+ x y) 2))

(defun good-enough? (guess x)
  (< (abs (- (square guess) x)) 0.001))

(defun square (x)
  (* x x))

(defun my-sqrt (x)
  (sqrt-iter 1.0 x))

;; For the small number, the absolute tolerance of 0.001 is significantly large. For example , (sqrt 0.0001) yields the value of 0.03230844833048122
;; For very large values of the radicand, the result will be overflow.Therefore, th function good-enough? would return false even though the number are actually within the threshold.

;; new good-enough?
(defun good-enough? (newguess oldguess)
  (< (abs (- newguess oldguess)) (* (abs oldguess) 1e-8)))

(defun sqrt-iter (newguess oldguess x)
  (if (good-enough? newguess oldguess)
	  newguess
	  (sqrt-iter (improve newguess x) newguess x)))

(defun sqrt-revise (x)
  (sqrt-iter 1.0 x x))
