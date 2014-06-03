;; Exercise 2.66: Implement the lookup procedure for the case
;; where the set of records is structured as a binary tree, or-
;; dered by the numerical values of the keys.


(defun lookup (given-key set-of-records)
  (if (null set-of-records)
	  nil
	  (let ((curr (entry set-of-records)))
		(let ((x (key (car curr))))
		  (cond ((= x given-key) curr)
				((< x given-key) (lookup given-key (left-branch set-of-records)))
				((> x given-key) (lookup given-key (left-branch set-of-records))))))))

