;; Exercise 1.5: Ben Bitdiddle has invented a test to determine
;; whether the interpreter he is faced with is using applicativeorder
;; evaluation or normal-order evaluation. He defines the
;; following two procedures:
(define (p) (p))
(define (test x y)
  (if (= x 0) 0 y))
;; Then he evaluates the expression
(test 0 (p))

;; if the interpreter uses applicative-order evaluation, then the expression
;; will fall in infinite loop
;; if the inpterpreter uses normal-order evaluation, the result will be 0.
