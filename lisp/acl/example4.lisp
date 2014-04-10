;;4.5 Example: Parsing Dates

(defun tokens (str test start)
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
		nil)))

;;4.7 Example: Binary Search Trees

(defstruct (node (:print-function
				  (lambda (n s d)
					(format s "#<~A>" (node-data n)))))
  (data nil) (l nil) (r nil))

(defun bst-insert (obj bst <)
  (print bst)
  (if (null bst)
	  (make-node :data obj)
	  (let ((elt (node-data bst)))
		(if (eql obj elt)
			bst
			(if (funcall < obj elt)
				(make-node
				 :data elt
				 :l (bst-insert obj (node-l bst) <)
				 :r (node-r bst))
				(make-node
				 :data elt
				 :r (bst-insert obj (node-r bst) <)
				 :l (node-l bst)))))))


(defun bst-find (obj bst <)
  (if (null bst)
	  nil
	  (let ((elt (node-data bst)))
		(if (eql obj elt)
			bst
			(if (funcall < obj elt)
				(bst-find obj (node-l bst) <)
				(bst-find obj (node-r bst) <))))))
