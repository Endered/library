(defstruct node
  (left nil)
  (right nil)
  (value nil))

(defstruct (segment-tree
	    (:constructor generate-segment-tree))
  (root nil)
  min max
  merge)

(defun make-segment-tree (&key (min 0) (max 0) (merge #'+))
  (assert (< min max))
  (generate-segment-tree :min min :max max
			 :merge merge))

(defmethod get-range ((tree segment-tree) left right)
  (with-slots (min max root merge) tree
    (let ((res nil)
	  (set nil))
      (labels ((in (l r)
		 (and (<= l left) (<= right r)))
	       (cross (l r)
		 (< (max l left) (min r right)))
	       (update (node)
		 (cond (set
			(setf res (funcall merge res (node-value node))))
		       (t
			(setf set t)
			(setf res (node-value node)))))
	       (rec (node l r)
		 (unless (cross l r)
		   (return-from rec))
		 (when (in l r)
		   (update node)
		   (return-from rec))
		 (let ((mid (ash (+ l r) -1))
		       (left-child (node-left node))
		       (right-child (node-right node)))
		   (when left-child (rec left-child l mid))
		   (when right-child (rec right-child mid r)))))
	(when root (rec root min max))
	(values res set)))))

(defmethod set-tree ((tree segment-tree) position value)
  (with-slots (min max root merge) tree
    (labels ((in (l r)
	       (and (<= l position) (< position r)))
	     (terminal (l r)
	       (= (1+ l) r))
	     (rec (node l r)
	       (unless node (setf node (make-node)))
	       (when (terminal l r)
		 (setf (node-value node) value)
		 (return-from rec node))
	       (let ((mid (ash (+ l r) -1)))
		 (with-slots (left right value) node
		   (cond ((< position mid)
			  (setf left
				(rec left l mid)))
			 (t
			  (setf right 
				(rec right mid r))))
		   (if (and left right)
		       (setf value (funcall merge (node-value left) (node-value right)))
		       (setf value (node-value (or left right))))))
	       node))
      (setf root (rec root min max)))))
