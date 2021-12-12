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
