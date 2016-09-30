;Copyright (c) Lebin Mathew Alex. All rights reserved.

(write-line "Enter n :")
(setq n (read))
(setf list (make-array n))
(terpri)

(write-line "Enter the numbers :")
(loop for i from 0 to (- n 1)
	do (setf (aref list i) (read)))

(terpri)
(write-line "Enter the number to be searched :")
(setq num (read))
(terpri)

(loop for i from 0 to (- n 1)
	do (if (= (aref list i) num) (progn (format t "Item found at ~d." i) (exit))))
	
(write-line "Item not found!")
