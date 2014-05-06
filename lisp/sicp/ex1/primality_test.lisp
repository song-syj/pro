(defun expmod (base exp m)
	(cond ((= exp 0) 1)
		  ((evenp exp) (mod (square (expmod base (/ exp 2) m))
							m))
		  (t (mod (* base (expmod base (- exp 1) m)) m))))

;; (defun fermat-test (n)
;;   (setf (symbol-function 'try-it)
;; 		#'(lambda (a)
;; 			(= (expmod a n n) a)))
;;   (try-it (+ 1 (random (- n 1)))))

(defun fermat-test (n)
  (labels ((try-it (a)
			 (= (expmod a n n) a)))
	(try-it (+ 1 (random (- n 1))))))


(defun fast-prime? (n times)
  (cond ((= times 0) t)
		((fermat-test n) (fast-prime? n (- times 1)))
		(t nil)))

(defun square (x)
  (* x x))

(defun smallest-divisor (n)
  (find-divisor n 2))

(defun find-divisor (n test-divisor)
  (cond ((> (square test-divisor) n) n)
		((divides? test-divisor n) test-divisor)
		(t (find-divisor n (+ test-divisor 1)))))

(defun divides? (a b)
  (= (mod b a) 0))

(defun prime? (n)
  (= (smallest-divisor n) n))
