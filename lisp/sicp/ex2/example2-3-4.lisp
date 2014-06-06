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

