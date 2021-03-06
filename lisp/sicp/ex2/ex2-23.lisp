;; Exercise 2.23: The procedure for-each is similar to map . It
;; takes as arguments a procedure and a list of elements. How-
;; ever, rather than forming a list of the results, for-each just
;; applies the procedure to each of the elements in turn, from
;; let to right. The values returned by applying the procedure
;; to the elements are not used at all— for-each is used with
;; procedures that perform an action, such as printing. For ex-
;; ample,
;; (for-each (lambda (x)
;; 			(newline)
;; 			(display x))
;; 		  (list 57 321 88))
;; 57
;; 321
;; 88
;; The value returned by the call to for-each (not illustrated
;; above) can be something arbitrary, such as true. Give an
;; implementation of for-each .

(defun for-each (proc items)
  (if (null items)
	  t
	  (progn (funcall proc (car items))
			  (for-each proc (cdr items)))))
