;; Exercise 2.39: Complete the following deﬁnitions of reverse
;; (Exercise 2.18) in terms of fold-right and fold-left from
;; Exercise 2.38:
;; (define (reverse sequence)
;; (fold-right (lambda (x y) ⟨ ?? ⟩ ) nil sequence))
;; (define (reverse sequence)
;; (fold-left (lambda (x y) ⟨ ?? ⟩ ) nil sequence))

(defun reverse-fold (sequence)
  (fold-right #'(lambda (x y)
				  (append y (list x)))
			  nil
			  sequence))

(defun reverse-fold (sequence)
  (fold-left #'(lambda (x y)
				 (append (list y) x))
				 nil
				 sequence))
