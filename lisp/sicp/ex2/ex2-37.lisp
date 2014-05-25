Exercise 2.37: Suppose we represent vectors v = (vi ) as se-
quences of numbers, and matrices m = (mi j ) as sequences
of vectors (the rows of the matrix). For example, the matrix
/  2 3 4 \
|  5 6 6 |
\  7 8 9 /
;; is represented as the sequence ((1 2 3 4) (4 5 6 6)
;; (6 7 8 9)) . With this representation, we can use sequence
;; operations to concisely express the basic matrix and vector
;; operations. These operations (which are described in any
;; book on matrix algebra) are the following:
;; (dot-product v w) returns the sum Σiviwi ,
;; (matrix-*-vector m v) returns the vector t,
;; where ti = Σjmi jvj ,
;; (matrix-*-matrix m n) returns the matrix p,
;; where pi j = Σkmiknk j ,
;; (transpose m) returns the matrix n,
;; where ni j = mji .
;; We can deﬁne the dot product as17
;; (define (dot-product v w)
;; 	(accumulate + 0 (map * v w)))
;; Fill in the missing expressions in the following procedures
;; for computing the other matrix operations. (The procedure
;; accumulate-n is deﬁned in Exercise 2.36.)
;; (define (matrix-*-vector m v)
;; 	(map ⟨ ?? ⟩ m))

(defun dot-product (v w)
  (accumulate #'+ 0 (mapcar * v w)))

(defun matrix-*-verctor (m v)
  (mapcar #'(lambda (row)
			  (dot-product v row)) m))

(defun accumulate (op initial sequence)
  (if (null sequence)
	  initial
	 (funcall op (car sequence)
			  (accumulate op initial (cdr sequence)))))

(defun accumulate-n (op init seqs)
  (if (null (car seqs))
	  nil
	  (cons (accumulate op init (mapcar #'car seqs))
			(accumulate-n op init (mapcar #'cdr seqs)))))

(defun transpose (m)
  (accumulate-n #'cons nil m))

(defun matrix-*-matrix (m n)
  (let ((cols (transpose n)))
	(mapcar #'(lambda (row)
				(matrix-*-verctor cols row))
			m)))
