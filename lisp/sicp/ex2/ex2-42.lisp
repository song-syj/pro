;; Exercise 2.42: The “eight-queens puzzle” asks how to place
;; eight queens on a chessboard so that no queen is in check
;; from any other (i.e., no two queens are in the same row, col-
;; umn, or diagonal)

(defun adjoin-position (new-row k rest-of-queens)
  (cons (list new-row k) rest-of-queens))

(defun safe? (k positions)
  (let ((new-pos (car positions)))
	(labels ((safe-all? (j res-pos)
			   (let ((head (car res-pos)))
				 (if (= j 0)
					 t
					 (and (/= (car new-pos) (car head))
						  (/= (abs (- (car new-pos) (car head)))
							  (abs (- (cadr new-pos) (cadr head))))
						  (safe-all? (- j 1) (cdr res-pos)))))))
	  (safe-all? (- k 1) (cdr positions)))))

(defun queens (board-size)
  (labels ((queen-cols (k)
			 (if (= k 0)
				 (list nil)
				 (filter
				  #'(lambda (positions)
				  	  (safe? k positions))
				  (flatmap #'(lambda (rest-of-queens)
							   (mapcar #'(lambda (new-row)
										   (adjoin-position new-row k rest-of-queens))
									   (enumerate-interval 1 board-size)))
						   (queen-cols (- k 1)))))))
	(queen-cols board-size)))


