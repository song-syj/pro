;; Exercise 2.29: A binary mobile consists of two branches,
;; a left branch and a right branch. Each branch is a rod of
;; a certain length, from which hangs either a weight or an-
;; other binary mobile. We can represent a binary mobile us-
;; ing compound data by constructing it from two branches
;; (for example, using list ):
;; (define (make-mobile left right)
;; 	(list left right))
;; A branch is constructed from a length (which must be a
;; number) together with a structure , which may be either a
;; number (representing a simple weight) or another mobile:
;; (define (make-branch length structure)
;; 	(list length structure))
;; a. Write the corresponding selectors left-branch and
;; right-branch , which return the branches of a mobile,
;; and branch-length and branch-structure , which re-
;; turn the components of a branch.
;; b. Using your selectors, deﬁne a procedure total-weight
;; that returns the total weight of a mobile.
;; c. A mobile is said to be balanced if the torque applied by
;; its top-left branch is equal to that applied by its top-
;; 151right branch (that is, if the length of the left rod mul-
;; tiplied by the weight hanging from that rod is equal
;; to the corresponding product for the right side) and if
;; each of the submobiles hanging oﬀ its branches is bal-
;; anced. Design a predicate that tests whether a binary
;; mobile is balanced.
;; d. Suppose we change the representation of mobiles so
;; that the constructors are
;; (define (make-mobile left right) (cons left right))
;; (define (make-branch length structure)
;; 	(cons length structure))
;; How much do you need to change your programs to
;; convert to the new representation?

(defun make-mobile (left right)
  (list left right))

(defun make-branch (length structure)
  (list length structure))

(defun left-branch (mobile)
  (car mobile))

(defun right-branch (mobile)
  (cadr mobile))

(defun branch-length (branch)
  (car branch))

(defun branch-structure (branch)
  (cadr branch))

;; (defun total-weight (mobile)
;;   (if (atom mobile)
;; 	  mobile
;; 	  (+ (total-weight (branch-structure (left-branch mobile))) 
;; 		 (total-weight  (branch-structure (right-branch mobile))))))

;; (defun mobile-balanced? (mobile)
;;   (cond ((null mobile) nil)
;; 		((atom mobile) t)
;; 		(t (let* ((lb (left-branch mobile))
;; 				  (rb (right-branch mobile))
;; 				  (lm (branch-structure lb))
;; 				  (rm (branch-structure rb)))
;; 			 (and (= (* (branch-length lb) (total-weight lm))
;; 					 (* (branch-length rb) (total-weight rm)))
;; 				  (mobile-balanced? lm)
;; 				  (mobile-balanced? rm))))))

(defun branch-weight (branch)
  (let ((bs (branch-structure branch)))
	(if (atom bs)
		bs
		(total-weight bs))))

(defun total-weight (mobile)
  (+ (branch-weight (left-branch mobile))
	 (branch-weight (right-branch mobile))))

(defun branch-torque (branch)
  (* (branch-length branch) (branch-weight branch)))

(defun branch-balanced? (branch)
  (let ((bs (branch-structure branch)))
	(if (atom bs)
		t
		(mobile-balanced? bs))))

 (defun mobile-balanced? (mobile)
   (if (atom mobile)
	   t
	   (let ((lb (left-branch mobile))
			 (rb (right-branch mobile)))
		 (and (= (branch-torque lb)
				 (branch-torque rb))
			  (branch-balanced? lb)
			  (branch-balanced? rb)))))


(defun make-mobile (left right)
  (cons left right))

(defun make-branch (length structure)
  (cons length structure))

(defun left-branch (mobile)
  (car mobile))

(defun right-branch (mobile)
  (cdr mobile))

(defun branch-length (branch)
  (car branch))

(defun branch-structure (branch)
  (cdr branch))

