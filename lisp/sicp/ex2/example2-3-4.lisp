;; Example: Huffman Encoding Trees

(defun make-leaf (symbol weight)
  (list 'leaf symbol weight))

(defun leaf? (object)
  (eql  (car object) 'leaf))

(defun symbol-leaf (x) (cadr x))
(defun weight-leaf (x) (caddr x))

(defun make-code-tree (left right)
  (list left
		right
		(append (symbols left) (symbols right))
		(+ (weight left) (weight right))))

(defun left-branch (tree) (car tree))
(defun right-branch (tree) (cadr tree))

(defun symbols (tree)
  (if (leaf? tree)
	  (list (symbol-leaf tree))
	  (caddr tree)))

(defun weight (tree)
  (if (leaf? tree)
	  (weight-leaf tree)
	  (cadddr tree)))

(defun decode (bits tree)
  (labels ((decode-1 (bits current-branch)
			 (if (null bits)
				 nil
				 (let ((next-branch (choose-branch (car bits) current-branch)))
				   (if (leaf? next-branch)
					   (cons (symbol-leaf next-branch)
							 (decode-1 (cdr bits) tree))
					   (decode-1 (cdr bits) next-branch))))))
	(decode-1 bits tree)))

(defun choose-branch (bit branch)
  (cond ((= bit 0) (left-branch branch))
		((= bit 1) (right-branch branch))
		(t (error "bad bit -- CHOOSE-BRANCH ~A~%" bit))))

(defun adjoin-set (x set)
  (cond ((null set) (list x))
		((< (weight x) (weight (car set))) (cons x set))
		(t (cons (car set)
				 (adjoin-set x (cdr set))))))

(defun make-leaf-set (pairs)
  (if (null pairs)
	  nil
	  (let ((pair (car pairs)))
		(adjoin-set (make-leaf (car pair)
							   (cadr pair))
					(make-leaf-set (cdr pairs))))))

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
