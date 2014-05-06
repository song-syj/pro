;; Exercise 1.17: The exponentiation algorithms in this sec-
;; tion are based on performing exponentiation by means of
;; repeated multiplication. In a similar way, one can perform
;; integer multiplication by means of repeated addition. The
;; following multiplication procedure (in which it is assumed
;; that our language can only add, not multiply) is analogous
;; to the expt procedure:
(defun mul (a b)
  (if (= b 0)
	  0
	  (+ a (mul a (- b 1)))))
;; This algorithm takes a number of steps that is linear in b.
;; Now suppose we include, together with addition, opera-
;; tions double, which doubles an integer, and halve, which
;; divides an (even) integer by 2. Using these, design a mul-
;; tiplication procedure analogous to fast-expt that uses a
;; logarithmic number of steps.
(defun my-double (x)
  (* 2 x))
(defun my-halve (x)
  (/ x 2))

(defun fast-mul (a b)
  (cond ((= b 0) 0)
		((evenp b) (my-double (fast-mul a (my-halve b))))
		(t (+ a (fast-mul a (- b 1))))))

