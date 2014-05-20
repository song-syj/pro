;; Exercise 2.5: Show that we can represent pairs of nonneg-
;; ative integers using only numbers and arithmetic opera-
;; tions if we represent the pair a and b as the integer that is
;; the product 2 a 3 b . Give the corresponding deﬁnitions of the
;; procedures cons , car , and cdr .

(defun cons3 (a b)
  (* (expt 2 a) (expt 3 b)))

(defun car3 (c)
  (labels ((iter-mul (base r num)
			 (if (/= (mod r base) 0)
				 num
				 (iter-mul base (/ r base) (+ num 1)))))
	(iter-mul 2 c 0)))

(defun cdr3 (c)
  (labels ((iter-mul (base r num)
			 (if (/= (mod r base) 0)
				 num
				 (iter-mul base (/ r base) (+ num 1)))))
	(iter-mul 3 c 0)))
