(setf path (make-pathname :name "myfile"))
(setf str (open path :direction :output
			   :if-exists :supersede))
(format str "Something~%")
(close str)

(setf str (open path :direction :input))
(read-line str)
(close str)

(with-open-file (str path :direction :output
					 :if-exists :supersede)
  (format str "Something~%"))

(defun pseudo-cat (file)
  (with-open-file (str file :direction :input)
	(do ((line (read-line str nil 'eof)
			   (read-line str nil 'eof)))
		((eql line 'eof))
	  (format t "~A~%" line))))
