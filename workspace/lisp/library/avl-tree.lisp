;;; begin of definition avl-tree
(defpackage :avl-tree
  (:use :cl)
  (:export
   :define-avl-set))

(in-package :avl-tree)

(defmacro define-avl-set (struct-name
			   &key
			     (conc-name struct-name)
			     (compare #'<)
			     (element-type '*))
  (let* ((set struct-name)
	 (node (intern (format nil "~:@(~a-node~)" conc-name)))
	 (make-node (intern (format nil "~:@(make-~a~)" node)))
	 (node-left-child (intern (format nil "~:@(~a-left-child~)" node)))
	 (node-right-child (intern (format nil "~:@(~a-right-child~)" node)))
	 (node-value (intern (format nil "~:@(~a-value~)" node)))
	 (node-height (intern (format nil "~:@(~a-height~)" node)))
	 (node-update-height (intern (format nil "~:@(~a-update-height~)" node)))
	 (node-rotate-left (intern (format nil "~:@(~a-rotate-left~)" node)))
	 (node-rotate-right (intern (format nil "~:@(~a-rotate-right~)" node)))
	 (node-balance (intern (format nil "~:@(~a-balance~)" node)))
	 (node-make-balance-left (intern (format nil "~:@(~a-make-balance-left~)" node)))
	 (node-make-balance-right (intern (format nil "~:@(~a-make-balance-right~)" node)))
	 (iter (intern (format nil "~:@(~a-iter~)" conc-name)))
	 (iter-next (intern (format nil "~:@(~a-next~)" iter)))
	 (iter-prev (intern (format nil "~:@(~a-prev~)" iter)))
	 (iter-value (intern (format nil "~:@(~a-value~)" iter)))
	 (iter-eq (intern (format nil "~:@(~a-eq~)" iter)))
	 (%make-set (intern (format nil "~:@(%make-~a~)" conc-name)))
	 (make-set (intern (format nil "~:@(make-~a~)" conc-name)))
	 (set-insert (intern (format nil "~:@(~a-insert~)" conc-name)))
	 (set-erase (intern (format nil "~:@(~a-erase~)" conc-name)))
	 (set-find (intern (format nil "~:@(~a-find~)" conc-name)))
	 (set-min (intern (format nil "~:@(~a-min~)" conc-name)))
	 (set-max (intern (format nil "~:@(~a-max~)" conc-name)))
	 (set-upper-bound (intern (format nil "~:@(~a-upper-bound~)" conc-name)))
	 (set-lower-bound (intern (format nil "~:@(~a-lower-bound~)" conc-name)))
	 (set-has (intern (format nil "~:@(~a-has~)" conc-name)))
	 (set-size (intern (format nil "~:@(~a-size~)" conc-name)))
	 )
    `(progn
       (defstruct ,node
	 (left-child nil :type (or null ,node))
	 (right-child nil :type (or null ,node))
	 (value nil :type ,element-type)
	 (height 1 :type (integer 0)))
       (defun ,node-update-height (node)
	 (declare (,node node))
	 (with-slots (height left-child right-child) node
	   (setf height
		 (1+ (max (if left-child (,node-height left-child) 0)
			  (if right-child (,node-height right-child) 0))))))
       (defun ,node-balance (node)
	 (declare (,node node))
	 (with-slots (left-child right-child) node
	   (- (if right-child (,node-height right-child) 0)
	      (if left-child (,node-height left-child) 0))))
       (defun ,node-rotate-right (node)
	 (declare (,node node))
	 (let* ((left (,node-left-child node))
		(right (,node-right-child left)))
	   (setf (,node-left-child node) right)
	   (setf (,node-right-child left) node)
	   (,node-update-height node)
	   (,node-update-height left)
	   left))
       (defun ,node-rotate-left (node)
	 (declare (,node node))
	 (let* ((right (,node-right-child node))
		(left (,node-left-child right)))
	   (setf (,node-right-child node) left)
	   (setf (,node-left-child right) node)
	   (,node-update-height node)
	   (,node-update-height right)
	   right))
       (defun ,node-make-balance-left (node)
	 (declare (,node node))
	 (cond ((<= 2 (,node-balance node))
		(let ((right (,node-right-child node)))
		  (when (<= (,node-balance right) -1)
		    (setf (,node-right-child node) (,node-rotate-right right)))
		  (,node-rotate-left node)))
	       (t node)))
       (defun ,node-make-balance-right (node)
	 (declare (,node node))
	 (cond ((<= (,node-balance node) -2)
		(let ((left (,node-left-child node)))
		  (when (<= 1 (,node-balance left))
		    (setf (,node-left-child node) (,node-rotate-left left)))
		  (,node-rotate-right node)))
	       (t node)))
       (defun ,iter-next (iter)
	 (declare (list iter))
	 (unless iter (return-from ,iter-next nil))
	 (labels ((min-iter (iter)
		    (let* ((node (car iter))
			   (left (,node-left-child node)))
		      (if left
			  (min-iter (cons left iter))
			  iter)))
		  (right-down (iter)
		    (let* ((node (car iter))
			   (right (,node-right-child node)))
		      (when right
			(min-iter (cons right iter)))))
		  (up-parent (iter)
		    (when (cdr iter)
		      (destructuring-bind
			  (last . next) iter
			(if (eq last (,node-left-child (car next)))
			    next
			    (up-parent next))))))
	   (or (right-down iter) (up-parent iter))))
       (defun ,iter-prev (iter)
	 (declare (list iter))
	 (unless iter (return-from ,iter-prev nil))
	 (labels ((max-iter (iter)
		    (let* ((node (car iter))
			   (right (,node-right-child node)))
		      (if right
			  (max-iter (cons right iter))
			  iter)))
		  (left-down (iter)
		    (let* ((node (car iter))
			   (left (,node-left-child node)))
		      (when left
			(max-iter (cons left iter)))))
		  (up-parent (iter)
		    (when (cdr iter)
		      (destructuring-bind
			  (last . next) iter
			(if (eq last (,node-right-child (car next)))
			    next
			    (up-parent next))))))
	   (or (left-down iter) (up-parent iter))))
       (defun ,iter-value (iter)
	 (declare (list iter))
	 (unless iter (error "ERROR INVALID ITERATOR"))
	 (,node-value (car iter)))
       (defun ,iter-eq (iter1 iter2)
	 (declare (list iter1 iter2))
	 (or (and (null iter1) (null iter2))
	     (eq (car iter1) (car iter2))))
       (defstruct (,set (:constructor ,%make-set))
	 (root nil :type (or null ,node))
	 (count 0 :type (integer 0)))
       (defun ,make-set ()
	 (,%make-set :root nil :count 0))
       (defun ,set-insert (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (count root) set
	   (labels ((rec (node)
		      (declare ((or null ,node) node))
		      (unless node
			(incf count)
			(return-from rec (,make-node :value key)))
		      (with-slots (left-child right-child value) node
			(cond ((funcall ,compare key value)
			       (setf left-child (rec left-child))
			       (,node-update-height node)
			       (,node-make-balance-right node))
			      ((funcall ,compare value key)
			       (setf right-child (rec right-child))
			       (,node-update-height node)
			       (,node-make-balance-left node))
			      (t (setf (,node-value node) key)
				 node)))))
	     (setf root (rec root)))))
       (defun ,set-erase (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (count root) set
	   (labels ((rec (node key)
		      (declare ((or null ,node) node) (,element-type key))
		      (unless node
			(return-from rec nil))
		      (with-slots (left-child right-child value) node
			(cond ((funcall ,compare key value)
			       (setf left-child (rec left-child key))
			       (,node-update-height node)
			       (,node-make-balance-left node))
			      ((funcall ,compare value key)
			       (setf right-child (rec right-child key))
			       (,node-update-height node)
			       (,node-make-balance-right node))
			      (t
			       (cond (right-child
				      (let ((minimum (minimum right-child)))
					(setf (,node-value node) minimum)
					(setf right-child (rec right-child minimum))
					(,node-update-height node)
					(,node-make-balance-right node)))
				     (t (decf count)
					left-child))))))
		    (minimum (node)
		      (declare (,node node))
		      (with-slots (left-child) node
			(if left-child
			    (minimum left-child)
			    (,node-value node)))))
	     (setf root (rec root key)))))
       (defun ,set-find (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (root) set
	   (let ((iter nil))
	     (labels ((rec (node)
			(declare ((or null ,node) node))
			(unless node (return-from rec nil))
			(push node iter)
			(with-slots (left-child right-child value) node
			  (cond ((funcall ,compare key value)
				 (rec left-child))
				((funcall ,compare value key)
				 (rec right-child))
				(t
				 iter)))))
	       (rec root)))))
       (defun ,set-min (set)
	 (declare (,set set))
	 (with-slots (root) set
	   (let ((iter nil))
	     (labels ((rec (node)
			(declare ((or null ,node) node))
			(cond (node
			       (push node iter)
			       (rec (,node-left-child node)))
			      (t iter))))
	       (rec root)))))
       (defun ,set-max (set)
	 (declare (,set set))
	 (with-slots (root) set
	   (let ((iter nil))
	     (labels ((rec (node)
			(declare ((or null ,node) node))
			(cond (node
			       (push node iter)
			       (rec (,node-right-child node)))
			      (t iter))))
	       (rec root)))))
       (defun ,set-lower-bound (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (root) set
	   (labels ((rec (node iter)
		      (declare ((or null ,node) node))
		      (unless node (return-from rec nil))
		      (with-slots (left-child right-child value) node
			(let ((next (cons node iter)))
			  (cond ((funcall ,compare key value)
				 (or (rec left-child next) next))
				((funcall ,compare value key)
				 (rec right-child next))
				(t next))))))
	     (rec root nil))))
       (defun ,set-upper-bound (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (root) set
	   (labels ((rec (node iter)
		      (declare ((or null ,node) node))
		      (unless node (return-from rec nil))
		      (with-slots (left-child right-child value) node
			(let ((next (cons node iter)))
			  (cond ((funcall ,compare key value)
				 (or (rec left-child next) next))
				((funcall ,compare value key)
				 (rec right-child next))
				(t nil))))))
	     (rec root nil))))
       (defun ,set-has (set key)
	 (declare (,set set) (,element-type key))
	 (with-slots (root) set
	   (labels ((rec (node)
		      (declare ((or null ,node) node))
		      (unless node (return-from rec nil))
		      (with-slots (left-child right-child value) node
			(cond ((funcall ,compare key value)
			       (rec left-child))
			      ((funcall ,compare value key)
			       (rec right-child))
			      (t
			       t)))))
	     (rec root))))
       (defun ,set-size (set)
	 (declare (,set set))
	 (with-slots (count) set
	   count)))))

(in-package :cl-user)
;;; end of definition


(avl-tree:define-avl-set binary-set :element-type integer :compare #'<)

;; example
(let ((set (make-binary-set)))
  (binary-set-insert set 1)
  (binary-set-insert set 3)
  (binary-set-insert set 5)
  (binary-set-erase set 3)
  (print (binary-set-has set 1)) ;; t
  (print (binary-set-has set 3)) ;; nil
  (print (binary-set-count set)) ;; 2
  (loop for i from 1 to 10
	do
	   (binary-set-insert set i))
  (print (binary-set-count set)) ;; 10
  (let* ((iter (binary-set-find set 9))
	 (prev (binary-set-iter-prev iter))
	 (next (binary-set-iter-next iter))
	 (next2 (binary-set-iter-next next)))
    (print (binary-set-iter-value iter)) ;; 9
    (print (binary-set-iter-value prev)) ;; 8
    (print (binary-set-iter-value next)) ;; 10
    (print next2) ;; nil
    ;; ERROR (print (binary-set-iter-value next2))
    )
  (let* ((iter (binary-set-lower-bound set 3)))
    (print (binary-set-iter-value iter)) ;; 3
    )
  (let* ((iter (binary-set-upper-bound set 3)))
    (print (binary-set-iter-value iter)) ;; 4
    )
  (print (binary-set-lower-bound set 11)) ;; nil
  (print (binary-set-upper-bound set 10)) ;; nil
  (print (binary-set-iter-value (binary-set-min set))) ;; 1
  (print (binary-set-iter-value (binary-set-max set))) ;; 10
  )
