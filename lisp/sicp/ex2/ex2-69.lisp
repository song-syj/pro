;; Exercise 2.69: e following procedure takes as its argu-
;; ment a list of symbol-frequency pairs (where no symbol
;; appears in more than one pair) and generates a Huffman
;; encoding tree according to the Huffman algorithm.
;; (define (generate-huffman-tree pairs)
;; (successive-merge (make-leaf-set pairs)))
;; Make-leaf-set is the procedure given above that trans-
;; forms the list of pairs into an ordered set of leaves. Successive-
;; merge is the procedure you must write, using make-code-
;; tree to successively merge the smallest-weight elements
;; of the set until there is only one element le, which is the
;; desired Huffman tree. (is procedure is slightly tricky, but
;; not really complicated. If you find yourself designing a com-
;; plex procedure, then you are almost certainly doing some-
;; thing wrong. You can take significant advantage of the fact
;; that we are using an ordered set representation.)

(defun generate-huffman-tree (pairs)
  (successive-merge (make-leaf-set pairs)))

(defun successive-merge (pairs)
  (if (null (cdr pairs))
	  (car pairs)
	  (let ((nod1 (car pairs))
			(nod2 (cadr pairs)))
		(successive-merge
		 (adjoin-set (make-code-tree nod1 nod2)
					 (cddr pairs))))))
