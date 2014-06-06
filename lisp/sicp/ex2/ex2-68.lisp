;; Exercise 2.68: e encode procedure takes as arguments a
;; message and a tree and produces the list of bits that gives
;; the encoded message.
;; (define (encode message tree)
;; 	(if (null? message)
;; 		'()
;; 		(append (encode-symbol (car message) tree)
;; 				(encode (cdr message) tree))))
;; is a procedure, which you must write, that
;; returns the list of bits that encodes a given symbol accord-
;; ing to a given tree. You should design encode-symbol so
;; that it signals an error if the symbol is not in the tree at all.
;; Test your procedure by encoding the result you obtained in
;; Exercise 2.67 with the sample tree and seeing whether it is
;; the same as the original sample message.

(defun encode (message tree)
  (if (null message)
	  nil
	  (append (encode-symbol (car message) tree)
			  (encode (cdr message) tree))))

(defun encode-symbol (symbol tree)
 (labels ((choose-symbol (symbol tree bits)
			(if (member symbol (symbols tree))
				(if (leaf? tree)
					(reverse bits)
					(let ((left (left-branch tree))
						  (right (right-branch tree)))
					  (cond ((member symbol (symbols left))
							 (choose-symbol symbol left (cons 0 bits)))
							(t (choose-symbol symbol right (cons 1 bits))))))
				(error "bad symbol -- CHOOSE-SYMBOL ~A~%" symbol))))
   (choose-symbol symbol tree nil)))

