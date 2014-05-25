;; Exercise 2.35: Redeﬁne count-leaves from Section 2.2.2
;; as an accumulation:
;; (define (count-leaves t)
;; 	(accumulate ⟨ ?? ⟩ ⟨ ?? ⟩ (map ⟨ ?? ⟩ ⟨ ?? ⟩ )))

(defun accumulate (op initial sequence)
  (if (null sequence)
	  initial
	 (funcall op (car sequence)
			  (accumulate op initial (cdr sequence)))))

(defun count-leaves (tree)
  (accumulate #'+ 0 (mapcar #'(lambda (x)
								(if (null x)
									1
									(count-leaves x)))
							tree)))
