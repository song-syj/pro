;; Exercise 1.10: The following procedure computes a math-
;; ematical function called Ackermann’s function.
(defun A (x y)
  (cond ((= y 0) 0)
		((= x 0) (* 2 y))
		((= y 1) 2)
		(t (A (- x 1) (A x (- y 1))))))
;; What are the values of the following expressions?
(A 1 10)
(A 2 4)
(A 3 3)
;; Consider the following procedures, where A is the procedure deﬁned above:
(defun f (n) (A 0 n))
(defun g (n) (A 1 n))
(defun h (n) (A 2 n))
(defun k (n) (* 5 n n))
;; Give concise mathematical deﬁnitions for the functions computed
;; by the procedures f , g , and h for positive integer values of n.
;; For example, (k n) computes 5n2.
;; f(n) = 2n
;; g(n) = 2^n, (n > 0); g(n) = 0, (n = 0)
;; h(n) = 2^h(n-1), (n>1); h(n) = 2(n =1); h(n) = 0(n = 0);
