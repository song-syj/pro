;; 5-1
(defconstant month
  #(0 31 59 90 120 151 181 212 243 273 304 334 365))
(defconstant yzero 2000)

(defun leap? (year)
  (destructuring-bind (fh h f)
	  (mapcar #'(lambda (n) (zerop (mod year n))) '(400 100 4))
	(or fh (and (not h) f))))

(defun date->num (d m y)
  (+ (- d 1) (month-num m y) (year-num y)))

(defun month-num (m y)
  (+ (svref month (- m 1))
	 (if (and (> m 2) (leap? y)) 1 0)))

(defun year-num (y)
  (let ((d 0))
	(if (>= y yzero)
		(dotimes (i (- y yzero) d)
		  (incf d (year-days (+ yzero i))))
		(dotimes (i (- yzero y) (- d))
		  (incf d (year-days (+ y i)))))))

(defun year-days (y)
  (if (leap? y) 366 365))

;; 5-2
(defun num->date (n)
  (multiple-value-bind (y left) (num-year n)
	(multiple-value-bind (m d) (num-month left y)
	  (values d m y))))

(defun num-year (n)
  (if (< n 0)
	  (do* ((y (- yzero 1) (- y 1))
			(d (- (year-days y)) (- d (year-days y))))
		   ((<= d n) (values y (- n d))))
	  (do* ((y yzero (+ y 1))
			(prev 0 d)
			(d (year-days y) (+ d (year-days y))))
		   ((> d n) (values y (- n prev))))))

(defun num-month (n y)
  (if (leap? y)
	  (cond ((= n 59) (values 2 29))
			((> n 59) (nmon (- n 1)))
			(t (nmon n)))
	  (nmon n)))

(defun nmon (n)
  (let ((m (position n month :test #'<)))
	(values m (+ 1 (- n (svref month (- m 1)))))))


(defun date+ (d m y n)
  (num->date (+ (date->num d m y) n)))
