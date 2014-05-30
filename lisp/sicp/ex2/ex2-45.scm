;; Exercise 2.45: Right-split and up-split can be expressed
;; as instances of a general spliing operation. Deﬁne a pro-
;; cedure split with the property that evaluating
;; (define right-split (split beside below))
;; (define up-split (split below beside))
;; produces procedures right-split and up-split with the
;; same behaviors as the ones already deﬁned.

(define (split orig spl)
  (lambda (painter n)
	(if (= n 0)
		painter
		(let ((smaller ((split orig spl) painter (- n 1))))
		  (orig painter (spl smaller smaller))))))

(define right-split (split beside below))
(define upp-split (split below beside))
