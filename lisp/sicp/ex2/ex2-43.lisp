;; Exercise 2.43: Louis Reasoner is having a terrible time do-
;; ing Exercise 2.42. His queens procedure seems to work, but
;; it runs extremely slowly. (Louis never does manage to wait
;; long enough for it to solve even the 6 * 6 case.) When Louis
;; asks Eva Lu Ator for help, she points out that he has inter-
;; changed the order of the nested mappings in the flatmap ,
;; writing it as
;; (flatmap
;;  (lambda (new-row)
;;    (map (lambda (rest-of-queens)
;; 		  (adjoin-position new-row k rest-of-queens))
;; 		(queen-cols (- k 1))))
;;  (enumerate-interval 1 board-size))
;; Explain why this interchange makes the program run slowly.
;; Estimate how long it will take Louis’s program to solve the
;; eight-queens puzzle, assuming that the program in Exercise
;; 2.42 solves the puzzle in time T.

(defun queens (board-size)
  (labels ((queen-cols (k)
			 (if (= k 0)
				 (list nil)
				 (filter
				  #'(lambda (positions)
				  	  (safe? k positions))
				  (flatmap #'(lambda (new-row)
							   (mapcar 
								#'(lambda (rest-of-queens)
									(adjoin-position new-row k rest-of-queens))
								(queen-cols (- k 1))))
						   (enumerate-interval 1 board-size))))))
	(queen-cols board-size)))


