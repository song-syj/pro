(defun par1 (r1 r2)
  (div-interval (mul-interval r1 r2)
				(add-interval r1 r2)))
(defun par2 (r1 r2)
  (let ((one (make-interval 1 1)))
	(div-interval one (add-interval (div-interval one r1)
									(div-interval one r2)))))
;; any operation between two intervals will increase errors;

