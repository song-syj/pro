;; Use dotted-tail notation to write a procedure same-parity that
;; takes one or more integers and returns a list of all the ar-
;; guments that have the same even-odd parity as the ﬁrst
;; argument. For example,
;; (same-parity 1 2 3 4 5 6 7)
;; (1 3 5 7)
;; (same-parity 2 3 4 5 6 7)
;; (2 4 6)

(defun same-parity (head &rest rest-element)
  (if (evenp head)
	  (cons head (remove-if-not #'evenp rest-element))
	  (cons head (remove-if-not #'oddp rest-element))))


