;Tower of Hanoi
;;Copyright (c) Lebin Mathew Alex. All rights reserved.


(defun MoveTower (height from mid to) "Move disks to another tower"
	(if (>= height 1)
		(progn 
			(MoveTower (- height 1) from to mid)
			(format t "Move disk from ~d to ~d ~%" from to)
			(MoveTower (- height 1) mid from to)
		)
	)
)

(write-line "Enter no of disks :")
(setq n (read))
(MoveTower n 1 2 3)


