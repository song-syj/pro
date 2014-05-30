;; Exercise 2.55: Eva Lu Ator types to the interpreter the ex-
;; pression
;; (car ''abracadabra)
;; To her surprise, the interpreter prints back quote . Explain.

''abracadabra is interpreted as (quote (quote abracadabra))

