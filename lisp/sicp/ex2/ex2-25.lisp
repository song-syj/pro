;; Exercise 2.25: Give combinations of car s and cdr s that
;; will pick 7 from each of the following lists:
;; (1 3 (5 7) 9)
;; ((7))
;; (1 (2 (3 (4 (5 (6 7))))))

(cadr (caddr '(1 3 (5 7) 9)))
(car (car '((7))))
(cadr (cadr (cadr (cadr (cadr (cadr '(1 (2 (3 (4 (5 (6 7))))))))))))
