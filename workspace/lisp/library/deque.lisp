(defpackage :deque
  (:use :cl)
  (:export
   :deque :make-deque :deque-length :deque-empty-p
   :deque-front :deque-back
   :deque-push-front :deque-push-back :deque-pop-front :deque-pop-back))
(in-package :deque)

(defstruct (deque (:constructor %make-deque))
  front-index
  back-index
  data)

(defun make-deque (&rest init-form)
  (let* ((length (length init-form))
	 (init-length (ash 1 (integer-length length)))
	 (initial-array (make-array init-length)))
    (loop for v in init-form
	  for i from 0
	  do (setf (aref initial-array i) v))
    (%make-deque :front-index 0
		 :back-index length
		 :data initial-array)))

(defun next-index (deque index)
  (if (= (1+ index) (length (deque-data deque)))
      0
      (1+ index)))

(defun prev-index (deque index)
  (if (= index 0)
      (1- (length (deque-data deque)))
      (1- index)))

(defun adjust-deque (deque)
  (with-slots (front-index back-index data) deque
    (when (= front-index (next-index deque back-index))
      (let* ((length (length data))
	     (next-data (make-array (ash length 1))))
	(cond ((<= front-index back-index) 
	       (loop for i from front-index below back-index
		     for j from 0
		     do (setf (aref next-data j) (aref data i))))
	      (t
	       (loop for i from front-index below length
		     for j from 0
		     do (setf (aref next-data j) (aref data i)))
	       (loop for i from 0 below back-index
		     for j from (- length front-index)
		     do (setf (aref next-data j) (aref data i)))))
	(setf back-index (deque-length deque))
	(setf front-index 0)
	(setf data next-data)))))

(defun deque-length (deque)
  (with-slots (front-index back-index data deque) deque
    (if (<= front-index back-index)
	(- back-index front-index)
	(+ back-index
	   (- (length data) front-index)))))

(defun deque-empty-p (deque)
  (with-slots (front-index back-index) deque
    (= front-index back-index)))

(defun deque-front (deque)
  (with-slots (front-index data) deque
    (aref data front-index)))

(defun deque-back (deque)
  (with-slots (back-index data) deque
    (aref data (prev-index deque back-index))))

(defun deque-push-front (deque value)
  (adjust-deque deque)
  (with-slots (front-index data) deque
    (setf front-index (prev-index deque front-index))
    (setf (aref data front-index) value)))
(defun deque-push-back (deque value)
  (adjust-deque deque)
  (with-slots (back-index data) deque
    (setf (aref data back-index) value)
    (setf back-index (next-index deque back-index))))

(defun deque-pop-front (deque)
  (with-slots (front-index data) deque
    (prog1
	(aref data front-index)
      (setf front-index (next-index deque front-index)))))
(defun deque-pop-back (deque)
  (with-slots (back-index data) deque
    (progn
      (setf back-index (prev-index deque back-index))
      (aref data back-index))))

(in-package :cl-user)
