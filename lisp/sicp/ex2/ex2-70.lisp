;; Exercise 2.70: The following eight-symbol alphabet with
;; associated relative frequencies was designed to efficiently
;; encode the lyrics of 1950s rock songs. (Note that the “sym-
;; bols” of an “alphabet” need not be individual letters.)
;; A
;; 2 GET 2 SHA 3 WAH 1
;; BOOM 1 JOB 2 NA 16 YIP 9
;; Use generate-huffman-tree (Exercise 2.69) to generate a
;; corresponding Huffman tree, and use encode (Exercise 2.68)
;; to encode the following message:
;; Get a job
;; Sha na na na na na na na na
;; Get a job
;; Sha na na na na na na na na
;; Wah yip yip yip yip yip yip yip yip yip
;; Sha boom
;; How many bits are required for the encoding? What is the
;; smallest number of bits that would be needed to encode this
;; song if we used a fixed-length code for the eight-symbol
;; alphabet?

(setf table '((A 2) (GET 2) (SHA 3) (WAH 1)
				  (BOOM 1) (JOB 2) (NA 16) (YIP 9)))
(setf tree (generate-huffman-tree table))
(setf message '(Get a job
				  Sha na na na na na na na na
				  Get a job
				  Sha na na na na na na na na
				  Wah yip yip yip yip yip yip yip yip yip
				  Sha boom))
(setf msg-encode (encode message tree))
