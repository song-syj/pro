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

;; 3
(defun n-arv (&rest arg)
  arg)

;; 4 most

(defun most (fn lst)
  (if (null lst)
	  (values nil nil)
	  (let* ((n1 (car lst))
			 (n2 (cadr lst))
			 (fir (funcall fn n1))
			 (sec (funcall fn n2)))
		   (when (< fir sec)
			 (rotatef fir sec)
			 (rotatef n1 n2))
		   (dolist (x lst (values n1 n2))
			 (let ((val (funcall fn x)))
			   (cond ((< fir val) (setf n2 n1 sec fir n1 x fir val))
					 ((< sec val) (setf n2 x sec x))
					 (t nil)))))))
;;5
(defun my-remove-if (fn lst)
  (let ((acc nil))
	(dolist (x lst)
	  (and (null (funcall fn x))
		   (push x acc)))
	(nreverse acc)))

;; 6
(let ((max nil))
  (defun max-so-for(num)
	(if (null max)
		(setf max num)
		(if (< max num)
			(setf max num)))
	max))

;; 7
(let ((prev nil))
  (defun larger-prev (num)
	(let ((prev1 prev))
	  (setf prev num)
	  (and prev1
		   (< prev1 num)))))

;; 8

(let ((vec (make-array 101 :intial-element nil)))
  (defun frugal (n)
	(when (null (aref vec n))
	  (setf (aref vec n) t)
	  (expensive n))))

;; 9
(defun my-apply (fn &rest arg)
  (let ((*print-base* 8))
	(print (apply fn arg))))
