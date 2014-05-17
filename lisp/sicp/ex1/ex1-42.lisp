;; Exercise 1.42: Let f and д be two one-argument functions.
;; The composition f after д is defined to be the function x →
;; f (д(x)). Define a procedure compose that implements com-
;; position. For example, if inc is a procedure that adds 1 to
;; its argument,
;; ((compose square inc) 6)

(defun compose (f g)
  (lambda (x)
	(funcall f (funcall g x))))

(defun square (x)
  (* x x))

(defun inc (x)
  (+ x 1))

