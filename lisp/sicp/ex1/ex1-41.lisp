;; Exercise 1.41: Define a procedure double that takes a procedure
;; of one argument as argument and returns a procedure that applies
;; the original procedure twice. For example, if inc is a procedure
;; that adds 1 to its argument, then (double inc) should be a procedure
;; that adds 2. What value is returned by
;; (((double (double double)) inc) 5)

(defun double-fun (f)
  (lambda (x)
	(funcall f (funcall f x))))

(funcall (funcall (double-fun (double-fun #'double-fun)) #'(lambda (x) (+ x 1))) 5)

(defun inc (x)
  (+ x 1))

(funcall (funcall (double-fun (double-fun #'double-fun)) #'inc) 5)
