;; 1. Define a function that takes a filename and returns a list of strings
;; representing each line in the file.

(defun file-list-str (filename)
  (with-open-file (str filename :direction :input)
	  (do ((line (read-line str nil :eof)
				 (read-line str nil :eof))
		   (acc nil (cons line acc)))
		  ((eql line :eof) (reverse acc)))))

;; 2. Define a function that takes a filename and returns a list of the
;; expressions in the file.

(defun file-list-exp (filename)
  (with-open-file (str filename :direction :input)
	(do ((exp (read str nil :eof)
			  (read str nil :eof))
		 (acc nil (cons exp acc)))
		((eql exp :eof)) (reverse acc))))

;; 3. Suppose that in some format for text files, comments are indicated by
;; a %, character. Everything from this character to the end of the line is
;; ignored. Define a function that takes two filenames, and writes to the
;; second file a copy of the first, minus comments.

(defun file-without-comment (infile outfile)
  (with-open-file (instr infile :direction :input)
	(with-open-file (outstr outfile :direction :output
							:if-exists :supersede)
	  (do ((c (read-char instr nil :eof)
			  (read-char instr nil :eof)))
		  ((eql c :eof))
		(if (char= c #\%)
			(read-line instr nil :eof)
			(princ c outstr))))))

;; 4. Define a function that takes a two-dimensional array of floats and
;; displays it in neat columns. Each element should be printed with two
;; digits after the decimal point, in a field 10 characters wide.
;; (Assume all will fit.) You will need array-dimensions (page 361).

(defun print-matrix (arr)
  (let ((dim (array-dimensions arr)))
	(dotimes (i (first dim))
	  (dotimes (j (second dim))
		(format t "~10,2F" (aref arr i j))) 
	  (terpri))))

;; 5. Modify stream-subst to allow wildcards in the pattern. If the char-
;; acter + occurs in old, it should match any input character.

(defun stream-subst (old new in out)
  (let* ((pos 0)
		 (len (length old))
		 (buf (new-buf len))
		 (from-buf nil))
	(do ((c (read-char in nil :eof)
			(or (setf from-buf (buf-next buf))
				(read-char in nil :eof))))
		((eql c :eof))
	  (cond ((or (char= (char old pos) #\+)
				 (char= c (char old pos)))
			 (incf pos)
			 (cond ((= pos len)
					(princ new out)
					(setf pos 0)
					(buf-clear buf))
				   ((not from-buf)
					(buf-insert c buf))))
			((zerop pos)
			 (princ c out)
			 (when from-buf
			   (buf-pop buf)
			   (buf-reset buf)))
			(t
			 (unless from-buf
			   (buf-insert c buf))
			 (princ (buf-pop buf) out)
			 (buf-reset buf)
			 (setf pos 0))))
	(buf-flush buf out)))


;; 6. Modify stream-subst so that the pattern can include an element that
;; matches any digit character, an element that matches any alphanumeric
;; character, or an element that matches any character. The pattern must
;; also be able to match any specific input character.
;; (Hint: old can no longer be a string.)

