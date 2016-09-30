;Copyright (c) Lebin Mathew Alex. All rights reserved.

(write-line "Enter n :")
(setq n (read))
(setf list (make-array n))
(terpri)
(write-line "Enter the numbers :")
(loop for i from 0 to (- n 1)
	do (setf (aref list i) (read)))

(terpri)
(write-line "The prime numbers are :")

(loop for i from 0 to (- n 1)
	do (progn (progn (setq prime 1) (if (= 0 (aref list i)) (setq prime 0)) (if (= 1 (aref list i)) (setq prime 0)) (loop for j from 2 to (/ (aref list i) 2)
		do (if (= (mod (aref list i) j) 0) (setq prime 0))))
		(if (= 1 prime) (format t "~d  " (aref list i)))))

