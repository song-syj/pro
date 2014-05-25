;; Exercise 2.33: Fill in the missing expressions to complete
;; the following deﬁnitions of some basic list-manipulation
;; operations as accumulations:
;; (define (map p sequence)
;; 	(accumulate (lambda (x y) ⟨ ?? ⟩ ) nil sequence))
;; (define (append seq1 seq2)
;; 	(accumulate cons ⟨ ?? ⟩ ⟨ ?? ⟩ ))
;; (define (length sequence)
;; 	(accumulate ⟨ ?? ⟩ 0 sequence))

(defun accumulate (op initial sequence)
  (if (null sequence)
	  initial
	 (funcall op (car sequence)
			  (accumulate op initial (cdr sequence)))))

(defun map-acc (p sequence)
  (accumulate #'(lambda (x y)
				  (cons (funcall p x) y))
			  nil sequence))

(defun append-acc (seq1 seq2)
  (accumulate #'cons seq2 seq1))

(defun length-acc (sequence)
  (accumulate #'(lambda (x y)
				  (+ 1 y))
			  0 sequence))

;; Exercise 2.34: Evaluating a polynomial in x at a given value
;; of x can be formulated as an accumulation. We evaluate the
;; polynomial
;; an*x^n + an-1*x^(n-1) + ........+ a1*x + a0
;; using a well-known algorithm called Horner’s rule, which
;; structures the computation as
;; ( . . . (anx + an-1) * x + .. + a1)x + a0 .
;; In other words, we start with an , multiply by x, add an-1,
;; multiply by x, and so on, until we reach a0.
;; Fill in the following template to produce a procedure that
;; evaluates a polynomial using Horner’s rule. Assume that
;; the coeﬃcients of the polynomial are arranged in a sequence,
;; from a0 through an .
;; (define (horner-eval x coefficient-sequence)
;; 	(accumulate (lambda (this-coeff higher-terms) ⟨ ?? ⟩ )
;; 				0
;; 				coefficient-sequence))

(defun horner-eval (x coefficient-sequence)
  (accumulate #'(lambda (this-coeff higher-terms)
				  (+ this-coeff (* x higher-terms)))
			  0
			  coefficient-sequence))
