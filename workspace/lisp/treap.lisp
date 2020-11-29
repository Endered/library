(defmacro aif (expr then &optional else)
  `(let ((it ,expr))
     (if it
         ,then
         ,else)))

(defstruct treap-node
  val
  (key 0)
  (left nil)
  (right nil))


(defstruct treap
  (comp #'<)
  (root nil)
  (size 0))


(defun change-treap-node (node &key
                                 (val (treap-node-val node))
                                 (key (treap-node-key node))
                                 (left (treap-node-left node))
                                 (right (treap-node-right node)))
  (make-treap-node :val val :key key
                   :left left :right right))


(defun rotate-right-node (node)
  (let* ((left (treap-node-left node))
         (left-right (treap-node-right left))
         (right (treap-node-right node)))
    (change-treap-node
     left
     :right (change-treap-node
             node
             :left left-right))))


(defun rotate-left-node (node)
  (let* ((right (treap-node-right node))
         (right-left (treap-node-left right))
         (left (treap-node-left node)))
    (change-treap-node
     right
     :left (change-treap-node
            node
            :right right-left))))


(defun tree-push (tree val)
  (let ((comp (treap-comp tree))
        (key (random 1000000))
        (root (treap-root tree))
        (size (treap-size tree)))
    (labels ((valance-left (node)
               (if (< (treap-node-key node)
                      (treap-node-key (treap-node-left node)))
                   node
                   (rotate-right-node node)))
             (valance-right (node)
               (if (< (treap-node-key node)
                      (treap-node-key (treap-node-right node)))
                   node
                   (rotate-left-node node)))
             (ins (node)
               (if node
                   (if (funcall comp val (treap-node-val node))
                       (valance-left
                        (change-treap-node
                         node
                         :left (ins (treap-node-left node))))
                       (valance-right
                        (change-treap-node
                         node
                         :right (ins (treap-node-right node)))))
                   (make-treap-node
                    :val val
                    :key key))))
      (make-treap
       :comp comp
       :root (ins root)
       :size (1+ size)))))

(defun tree-pop (tree val)
  (let ((comp (treap-comp tree))
        (root (treap-root tree))
        (size (treap-size tree)))
    (labels ((del (node &aux (node-val (treap-node-val node)))
               (cond ((funcall comp val node-val)
                      (change-treap-node
                       node
                       :left (del (treap-node-left node))))
                     ((funcall comp node-val val)
                      (change-treap-node
                       node
                       :right (del (treap-node-right node))))
                     (t
                      (let ((left-node (treap-node-left node))
                            (right-node (treap-node-right node)))
                        (cond ((null (or left-node right-node))
                               nil)
                              ((and left-node right-node)
                               (if (< (treap-node-key left-node)
                                      (treap-node-key right-node))
                                   (del (rotate-right-node node))
                                   (del (rotate-left-node node))))
                              (left-node
                               left-node)
                              (right-node
                               right-node)))))))
      (make-treap
       :comp comp
       :root (del root)
       :size (1- size)))))


(defun tree-push! (tree val)
  (let ((new (tree-push tree val)))
    (setf (treap-root tree) (treap-root new))
    (setf (treap-size tree) (treap-size new))))

(defun tree-pop! (tree val)
  (let ((new (tree-pop tree val)))
    (setf (treap-root tree) (treap-root new))
    (setf (treap-size tree) (treap-size new))))

(defun tree-find (tree val)
  (let ((comp (treap-comp tree))
        (root (treap-root tree)))
    (labels ((f (node)
               (if node
                   (let ((node-val (treap-node-val node)))
                     (cond ((funcall comp val node-val)
                            (f (treap-node-left node)))
                           ((funcall comp node-val val)
                            (f (treap-node-right node)))
                           (t t)))
                   nil)))
      (f root))))

(defun tree-min (tree)
  (labels ((f (node)
             (aif (treap-node-left node)
                  (f it)
                  (treap-node-val node))))
    (f (treap-root tree))))

(defun tree-max (tree)
  (labels ((f (node)
             (aif (treap-node-right node)
                  (f it)
                  (treap-node-val node))))
    (f (treap-root tree))))

