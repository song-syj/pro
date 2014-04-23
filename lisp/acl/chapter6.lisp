;; 1.Define a version of tokens (page 67) that takes :test and :start
;;   arguments defaulting to # ' c o n s t i t u e n t and 0 respectively.
(defun tokens (str &key (test #'constituent) (start 0))
  (let ((p1 (position-if test str :start start)))
	(if p1
		(let ((p2 (position-if #'(lambda (c)
								   (not (funcall test c)))
							   str :start p1)))
		  (cons (subseq str p1 p2)
				(and p2 (tokens str :test test :start p2)))))))

(defun constituent (c)
  (and (graphic-char-p c)
	   (not (char= c #\ ))))

;; 2. Define a version of bin-search (page 60) that takes :key, :test,
;; :start , and :end arguments with the usual meanings and defaults.

(defun bin-search (obj vec
				   &key (key #'identity)
					 (test #'eql)
					 (start 0)
					 (end nil))
  (let ((range (length (subseq vec start end))))
	(if (zerop range)
		(if (funcall test obj (funcall key  (aref vec start)))
			(aref vec start))
		(let ((mid (+ start (round (/ range 2)))))
		  (let ((val (funcall key (aref vec mid))))
			(if (< obj val)
				(bin-search obj vec :key key :test test :start start :end mid)
				(if (> obj val)
					(bin-search obj vec :key key :test test :start (+ mid 1) :end end)
					(aref vec mid))))))))

