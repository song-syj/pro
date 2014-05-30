;; Exercise 2.53: What would the interpreter print in response
;; to evaluating each of the following expressions?

(list 'a 'b 'c)
(list (list 'george))
(cdr '((x1 x2) (y1 y2)))
(cadr '((x1 x2) (y1 y2)))
(consp (car '(a short list)))
(member 'red '((red shoes) (blue socks)))
(member 'red '(red shoes blue socks))
