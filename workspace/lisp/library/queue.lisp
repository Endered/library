(defpackage :queue
  (:use :cl)
  (:export :queue :make-queue :queue-size :enqueue :dequeue :queue-empty-p :queue-front))
(in-package :queue)

(defstruct (queue (:constructor %make-queue))
  st1
  st2
  size)

(defun make-queue (&rest init-form)
  (%make-queue
   :st1 init-form
   :st2 nil
   :size (length init-form)))

(defun enqueue (queue value)
  (with-slots (st2 size)
      queue
    (incf size)
    (push value st2)))

(defun dequeue (queue)
  (with-slots (st1 st2 size)
      queue
    (decf size)
    (unless st1
      (loop while st2
	    do (push (pop st2) st1)))
    (pop st1)))

(defun queue-front (queue)
  (with-slots (st1 st2)
      queue
    (unless st1
      (loop while st2
	    do (push (pop st2) st1)))
    (car st1)))

(defun queue-empty-p (queue)
  (zerop (queue-size queue)))
(in-package :cl-user)
