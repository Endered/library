(defmacro dp (name args memo-size &body body)
  (let ((memo (gensym)))
    `(let ((,memo (make-array ,memo-size :initial-element nil)))
       (defun ,name ,args
         (or (aref ,memo ,@args)
             (setf (aref ,memo ,@args)
                   ,@body))))))

(defun split (x str)
  (let ((pos (search x str))
        (size (length x)))
    (if pos
      (cons (subseq str 0 pos)
            (split x (subseq str (+ pos size))))
      (list str))))

