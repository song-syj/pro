;; 1.2.4 Exponentiation
(defun my-expt (b n)
  (cond ((= n 0) 1)
		((> n 0) (* b (my-expt b (- n 1))))
		((< n 0) (* (/ 1 b) (my-expt b (+ n 1))))))

(defun my-expt (b n)
  (if (< n 0)
	  (expt-iter (/ 1 b) (abs n) 1)
	  (expt-iter b n 1)))

(defun expt-iter (b counter product)
  (cond ((= counter 0) product)
		(t (expt-iter b (- counter 1) (* b product)))))

(defun fast-expt (b n)
  (cond ((= n 0) 1)
		((evenp n) (square (fast-expt b (/ n 2))))
		(t (* b (fast-expt b (- n 1))))))
(defun square (x)
  (* x x))

