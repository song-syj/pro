;; Exercise 1.9: Each of the following two procedures defines
;; a method for adding two positive integers in terms of the
;; procedures inc, which increments its argument by 1, and
;; dec, which decrements its argument by 1.
(defun add-recur (a b)
  (if (= a 0) b (inc (add-recur (dec a) b))))

(defun add-iter (a b)
  (if (= a 0) b (add-iter (dec a) (inc b))))

(defun inc (x)
  (+ x 1))

(defun dec (x)
  (- x 1))
;; Using the substitution model, illustrate the process gener-
;; ated by each procedure in evaluating (+ 4 5). Are these
;; processes iterative or recursive?
