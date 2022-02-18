(defpackage :persistent-array
  (:use :cl)
  (:nicknames :pa)
  (:export
   :make-persistent-array
   :pa-set
   :pa-get
   :pa-push
   :pa-pop))

(in-package :pa)

(defstruct node
  p1
  p0
  value)

(defun copy-node (node &key (p0 (node-p0 node)) (p1 (node-p1 node))
			 (value (node-value node)))
  (make-node :p0 p0 :p1 p1 :value value))

(defstruct (persistent-array (:constructor %make-persistent-array)
			     (:conc-name pa-))
  size
  root)

(defun make-persistent-array (n &optional (initial 0))
  (labels ((rec (pos add1)
	     (when (< pos n)
	       (let ((add2 (ash add1 1)))
		 (make-node
		  :p0 (rec (+ pos add1) add2)
		  :p1 (rec (+ pos add2) add2)
		  :value (if (functionp initial)
			     (funcall initial pos)
			     initial))))))
    (%make-persistent-array :size n :root (rec 0 1))))

(defun pa-get (pa p)
  (labels ((rec (node pos)
	     (when (zerop pos)
	       (return-from rec node))
	     (if (oddp pos)
		 (rec (node-p0 node) (ash (- pos 1) -1))
		 (rec (node-p1 node) (ash (- pos 2) -1)))))
    (node-value (rec (pa-root pa) p))))

(defun pa-set (pa p value)
  (labels ((rec (node pos)
	     (when (zerop pos)
	       (return-from rec (copy-node node :value value)))
	     (if (oddp pos)
		 (copy-node node :p0 (rec (node-p0 node) (ash (- pos 1) -1)))
		 (copy-node node :p1 (rec (node-p1 node) (ash (- pos 2) -1))))))
    (%make-persistent-array
     :size (pa-size pa)
     :root (rec (pa-root pa) p))))

(defun pa-push (pa value)
  (labels ((rec (node pos)
	     (when (zerop pos)
	       (return-from rec (make-node :p0 nil :p1 nil :value value)))
	     (if (oddp pos)
		 (copy-node node :p0 (rec (node-p0 node) (ash (- pos 1) -1)))
		 (copy-node node :p1 (rec (node-p1 node) (ash (- pos 2) -1))))))
    (%make-persistent-array
     :size (1+ (pa-size pa))
     :root (rec (pa-root pa) (pa-size pa)))))

(defun pa-pop (pa)
  (labels ((rec (node pos)
	     (when (zerop pos)
	       (return-from rec nil))
	     (if (oddp pos)
		 (copy-node node :p0 (rec (node-p0 node) (ash (- pos 1) -1)))
		 (copy-node node :p1 (rec (node-p1 node) (ash (- pos 2) -1))))))
    (%make-persistent-array
     :size (1- (pa-size pa))
     :root (rec (pa-root pa) (1- (pa-size pa))))))

(in-package :cl-user)

(defpackage :persistent-union-find
  (:use :cl)
  (:nicknames :puf)
  (:export
   :make-persistent-union-find
   ))

(in-package :puf)

(defstruct (persistent-union-find (:constructor %make-persistent-union-find)
				  (:conc-name puf-))
  size
  array)

(defun make-persistent-union-find (size)
  (%make-persistent-union-find :size size :array (pa:make-persistent-array size -1)))

(defun puf-get-parent (puf a)
  (with-slots (array ))
  (if (eq -1 (are))))

(in-package :cl-user)

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

(defun square (n)
  (* n n))

(defstruct point
  x y)

(defun point-dist (a b)
  (round (sqrt (+ (square (- (point-x a) (point-x b)))
		  (square (- (point-y a) (point-y b)))))))

(defun read-point ()
  (make-point :x (read) :y (read)))

(defstruct edge
  p1
  p2)

(defun read-edge ()
  (make-edge :p1 (read) :p2 (read)))

(defun response (n)
  (format t "~a~%" n)
  (force-output))

(defun adapt ()
  (response 1))

(defun reject ()
  (response 0))


(defvar node-number 400)
(defvar edge-number 1995)

(defvar nodes #())
(defvar edges #())


(defun dist (a b)
  (point-dist (aref nodes a) (aref nodes b)))

(defun main ()
  (let* ((uf (uf:make-union-find node-number))
	 (nodes (make-array node-number :element-type 'point :initial-contents
			    (loop repeat node-number collect (read-point))))
	 (edges (make-array edge-number :element-type 'edge :initial-contents
			    (loop repeat edge-number collect (read-edge)))))
    (loop for edge across edges
	  for p1 = (edge-p1 edge)
	  for p2 = (edge-p2 edge)
	  do
	     (cond ((uf:uf-same-p uf p1 p2)
		    (reject))
		   (t
		    (adapt)
		    (uf:uf-merge uf p1 p2))))))

#-swank
(main)
