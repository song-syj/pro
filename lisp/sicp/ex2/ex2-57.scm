#lang racket

(define (sum? x)
  (and (pair? x) (eq? (car x) '+)))

(define (product? x)
  (and (pair? x) (eq? (car x) '*)))

(define (accumulate op initial sequence)
  (if (null? sequence)
	  initial
	  (op (car sequence)
		  (accumulate op initial (cdr sequence)))))

(define (make-sum . l) 
  (let ((lst (if (null? (cdr l)) (car l) l))) ;-> if it's a list inside a list, fix that. 
	(let ((an (map (lambda (x) (if (and (pair? x) (sum? x)) 
								   (make-sum (cdr x)) 
								   x)) lst))) ;-> this will reduce inner sums. 
	  (let ((var-lst (filter (lambda (x) (not (number? x))) an)) ;-> make a list of variable 
			(total (accumulate + 0 (filter number? an)))) ;-> sum all the numbers 
		(cond ((null? var-lst) total) ;-> if  there are no variables, than the sum is total 
			  ((= total 0) (if (null? (cdr var-lst)) ;-> if total is zero, then return var-lst 
							   (car var-lst) ;-> if it has only one element return it 
							   (append (list '+) var-lst))) ;-> if it has more, then represent a 
										;list of the type (+ elements of var-lst) 
			  (else 
			   (append (list '+)  ;-> else, just give a sum 
					   var-lst 
					   total))))))) 
  
 (define (augend e) 
   (make-sum (cddr e))) 
  
 ; and make-product would be the same. 
  
 (define (make-product . l) 
   (let ((lst (if (null? (cdr l)) (car l) l))) 
     (let ((pn (map (lambda (x) (if (and (pair? x) (product? x)) 
                                    (make-product (cdr x)) 
                                    x)) lst))) 
       (let ((var-lst (filter (lambda (x) (not (number? x))) pn)) 
             (prod (accumulate * 1 (filter number? pn)))) 
         (cond ((null? var-lst) prod) 
               ((= prod 1)  
                (if (null? (cdr var-lst)) 
                    (car var-lst) 
                    (append (list '*) var-lst))) 
               ((= prod 0) 0) 
               (else 
                (append (list '*) 
                        var-lst 
                        (list prod)))))))) 
  
 (define (multiplicand p) 
   (make-product (cddr p))) 
