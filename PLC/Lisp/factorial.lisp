;Copyright (c) Lebin Mathew Alex. All rights reserved.

(setq fact 1)

(write-line "Enter the number :")
(setq n (read))
(terpri)

(loop for n from n downto 1
	do(setq fact (* fact n)))

(format t "Factorial = ~d" fact)
