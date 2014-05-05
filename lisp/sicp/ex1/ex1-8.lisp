;; Exercise 1.8: Newton’s method for cube roots is based on
;; the fact that if y is an approximation to the cube root of x,
;; then a better approximation is given by the value
;; (/ (+ (/ x (square y)) (* 2 y)) 3)
;; Use this formula to implement a cube-root procedure analogous
;; to the square-root procedure

(defun cube-root(x)
  (cube-root-iter 1.0 x x))

(defun cube-root-iter(new old x)
  (if (good-enough? new old)
	  new
	  (cube-root-iter (improve-cube new x) new x)))

(defun improve-cube(guess x)
  (/ (+ (/ x (square guess)) (* 2 guess)) 3))

(defun good-enough?(newguess oldguess)
  (< (abs (- newguess oldguess)) (* (abs oldguess) 1e-8)))

(defun square(x)
  (* x x))
