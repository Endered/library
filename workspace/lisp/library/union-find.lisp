(defpackage :union-find
  (:use :cl)
  (:nicknames :uf)
  (:export
   :make-union-find
   :uf-find-parent
   :uf-same-p
   :uf-merge
   :uf-group-size))

(in-package :union-find)

(defstruct (union-find (:constructor %make-union-find))
  size
  parents)

(defun make-union-find (size)
  (%make-union-find :size size :parents (make-array size :element-type 'integer :initial-element -1)))

(defun uf-find-parent (uf p)
  (with-slots (parents) uf
    (labels ((rec (p)
	       (if (minusp (aref parents p) p)
		   p
		   (setf (aref parents p) (rec (aref parents p))))))
      (rec p))))

(defun uf-same-p (uf a b)
  (eq (uf-find-parent uf a) (uf-find-parent uf b)))

(defun uf-merge (uf a b)
  (let ((ap (uf-find-parent uf a))
	(bp (uf-find-parent uf b)))
    (unless (eq a b)
      (with-slots (parents) uf
	(when (< (aref parents ap) (aref parents bp))
	  (rotatef ap bp))
	(incf (aref parents ap) (aref parents bp))
	(setf (aref parents bp) ap)))))

(defun uf-group-size (uf p)
  (- (aref (uf-parents uf) (uf-find-parent p))))

(in-package :cl-user)
