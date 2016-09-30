;Sort half of the array in ascending and the other half
;in descending order
;Copyright (c) Lebin Mathew Alex. All rights reserved.

(write-line "Enter n :")
(setq n (read))
(setf list (make-array n))
(terpri)

(setq mid (round (/ n 2)))

(write-line "Enter the numbers :")
(loop for i from 0 to (- n 1)
	do (setf (aref list i) (read)))

(terpri)

(loop for i from 0 to mid
	do (loop for j from 0 to (- mid 2)
		do (if (> (aref list j) (aref list (+ j 1))) (rotatef (aref list j) (aref list (+ j 1))))))

(loop for i from 0 to mid
	do (loop for j from mid to (- n 2)
		do (if (< (aref list j) (aref list (+ j 1))) (rotatef (aref 
		list j) (aref list (+ j 1))))))

(write-line "After sorting, list is :")
(terpri)

(loop for i from 0 to (- n 1)
	do (format t "~d  " (aref list i)))

