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

(format t "~10,5,1,'','_F" 996.21875d0)

;; Example: String Substitution
(defstruct buf
  vec (start -1) (used -1) (new -1) (end -1))

(defun bref (buf n)
  (svref (buf-vec buf)
		 (mod n (length (buf-vec buf)))))

(defun (setf bref) (val buf n)
  (setf (svref (buf-vec buf)
			   (mod n (length (buf-vec buf))))
		val))

(defun new-buf (len)
  (make-buf :vec (make-array len)))

(defun buf-insert (x b)
  (setf (bref b (incf (buf-end b))) x))

(defun buf-pop (b)
  (prog1
	  (bref b (incf (buf-start b)))
	(setf (buf-used b) (buf-start b)
		  (buf-new b) (buf-end b))))

(defun buf-next (b)
  (when (< (buf-used b) (buf-new b))
	(bref b (incf (buf-used b)))))

(defun buf-rest (b)
  (setf (buf-used b) (buf-start b)
		(buf-new b) (buf-end b)))

(defun buf-clear (b)
  (setf (buf-start b) -1 (buf-used b) -1
		(buf-new b) -1 (buf-end b) -1))

(defun buf-flush (b str)
  (do ((i (1+ (buf-used b)) (1+ i)))
	  ((> i (buf-end b)))
	(princ (bref b i) str)))


(defun stream-subst (old new in out)
  (let* ((pos 0)
         (len (length old))
         (buf (new-buf len))
         (from-buf nil))
    (do ((c (read-char in nil :eof)
            (or (setf from-buf (buf-next buf))
                (read-char in nil :eof))))
        ((eql c :eof))
      (cond ((char= c (char old pos))
             (incf pos)
             (cond ((= pos len)            ; 3
                    (princ new out)
                    (setf pos 0)
                    (buf-clear buf))
                   ((not from-buf)         ; 2
                    (buf-insert c buf))))
            ((zerop pos)                   ; 1
             (princ c out)
             (when from-buf
               (buf-pop buf)
               (buf-reset buf)))
            (t                             ; 4
             (unless from-buf
               (buf-insert c buf))
             (princ (buf-pop buf) out)
             (buf-reset buf)
             (setf pos 0))))
    (buf-flush buf out)))
