;;4.5 Example: Parsing Dates

#|(defun tokens (str test start)
  (let ((p1 (position-if test str :start start)))
	(if p1
		(let ((p2 (position-if #'(lambda (c)
								   (not (funcall test c)))
							   str :start p1)))
		  (cons (subseq str p1 p2)
				(if p2
					(tokens str test p2)
					nil)))
		nil)))

(defun constituent (c)
  (and (graphic-char-p c)
	   (not (char= c #\ ))))

(defun parse-date (str)
  (let ((toks (tokens str #'constituent 0)))
	(list (parse-integer (first toks))
		  (parse-month (second toks))
		  (parse-integer (third toks)))))

(defconstant month-names
  #("jan" "feb" "mar" "apr" "may" "jun"
	"jul" "aug" "sep" "oct" "nov" "dec"))

(defun parse-month (str)
  (let ((p (position str month-names
					 :test #'string-equal)))
	(if p
		(+ p 1)
		nil))) |#

;;4.7 Example: Binary Search Trees

(defstruct (node (:print-function
				  (lambda (n s d)
					(format s "#<~A>" (node-elt n)))))
  (elt nil) (l nil) (r nil))

(defun bst-insert (obj bst <)
  (print bst)
  (if (null bst)
	  (make-node :elt obj)
	  (let ((elt (node-elt bst)))
		(if (eql obj elt)
			bst
			(if (funcall < obj elt)
				(make-node
				 :elt elt
				 :l (bst-insert obj (node-l bst) <)
				 :r (node-r bst))
				(make-node
				 :elt elt
				 :r (bst-insert obj (node-r bst) <)
				 :l (node-l bst)))))))


(defun bst-find (obj bst <)
  (if (null bst)
	  nil
	  (let ((elt (node-elt bst)))
		(if (eql obj elt)
			bst
			(if (funcall < obj elt)
				(bst-find obj (node-l bst) <)
				(bst-find obj (node-r bst) <))))))

(defun bst-min (bst)
  (and bst
	   (or (bst-min (node-l bst)) bst)))

(defun bst-max (bst)
  (and bst
	   (or (bst-max (node-r bst)) bst)))

(defun bst-remove (obj bst <)
  (if (null bst)
	  nil
	  (let ((elt (node-elt bst)))
		(if (eql obj elt)
			(percolate bst)
			(if (funcall < obj elt)
				(make-node
				 :elt elt
				 :l (bst-remove obj (node-l bst) <)
				 :r (node-r bst))
				(make-node
				 :elt elt
				 :r (bst-remove obj (node-r bst) <)
				 :l (node-l bst)))))))

(defun percolate (bst)
  (let ((l (node-l bst))
		(r (node-r bst)))
	(cond ((null l) r)
		  ((null r) l)
		  (t (if (zerop (random 2))
				 (make-node
				  :elt (node-elt (bst-max l))
				  :r r
				  :l (bst-remove-max l))
				 (make-node
				  :elt (node-elt (bst-min r))
				  :l l
				  :r (bst-remove-min r)))))))

(defun bst-remove-max (bst)
  (if (null (node-r bst))
	  (node-l bst)
	  (make-node
	   :elt (node-elt bst)
	   :l (node-l bst)
	   :r (bst-remove-max (node-r bst)))))

(defun bst-remove-min (bst)
  (if (null (node-l bst))
	  (node-r bst)
	  (make-node
	   :elt (node-elt bst)
	   :l (bst-remove-min (node-l bst))
	   :r (node-r bst))))

(defun bst-traverse (fn bst)
  (when bst
	(bst-traverse fn (node-l bst))
	(funcall fn (node-elt bst))
	(bst-traverse fn (node-r bst))))

