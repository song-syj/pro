;; Exercise 2.1: Deﬁne a better version of make-rat that handles
;; both positive and negative arguments. Make-rat should normalize
;; the sign so that if the rational number is positive, both the
;; numerator and denominator are positive, and if the rational
;; number is negative, only the numerator is negative.

(defun make-rat (n d)
  (let ((g (funcall (if (< d 0) #'- #'+) (gcd n d))))
	(if (= d 0)
		(error " Denom can't be zero!")
		(cons (/ n g) (/ d g)))))

