(defmacro with-gensym (symbols &body body)
  `(let ,(mapcar (lambda (symbol)
		   `(,symbol (gensym)))
	  symbols)
     (declare (symbol ,@symbols))
     (progn ,@body)))

(defstruct promise
    func value evaluated)

(when t
  (defmacro lazy (&body body)
    `(make-promise :func (lambda () ,@body) :value nil :evaluated nil))
  (defun force (lazy-value)
    (with-slots (func value evaluated) lazy-value
      (unless evaluated
	(setf value (funcall func))
	(setf evaluated t)
	(setf func nil))
      value)))

(when nil
  (defmacro lazy (&body body)
    (with-gensym (value evaluated)
      `(let (,value ,evaluated)
	 (declare (symbol ,evaluated))
	 (lambda ()
	   (unless ,evaluated
	     (setf ,evaluated t)
	     (setf ,value (progn ,@body)))
	   ,value))))
  (defun force (lazy-value)
    (funcall lazy-value)))

(defmacro release (symbol)
  `(prog1 ,symbol (setf ,symbol nil)))

(defmacro lazy-cons (car cdr)
  `(lazy (cons ,car ,cdr)))
(defmacro lazy-list (&body list)
  (reduce (lambda (a b)
	    `(lazy-cons ,a ,b))
	  list
	  :from-end t
	  :initial-value nil))

(defmacro lazy-list* (&body list)
  (reduce (lambda (a b)
	    `(lazy-cons ,a ,b))
	  list
	  :from-end t))

(defun lcar (lazy-value)
  (when lazy-value (car (force lazy-value))))
(defun lcdr (lazy-value)
  (when lazy-value (cdr (force lazy-value))))
(defun nthlcdr (n lazy-value)
  (labels ((rec (n value)
	     (if (<= n 0)
		 value
		 (rec (1- n) (lcdr value)))))
    (rec n lazy-value)))
(defun lnull (lazy-value)
  (or (null lazy-value) (null (force lazy-value))))
(defun lnth (n lazy-value)
  (if (<= n 0)
      (lcar lazy-value)
      (lnth (1- n) (lcdr lazy-value))))

(defun make-lazy (list)
  (labels ((rec (list)
	     (when list
	       (lazy-cons (car list) (rec (cdr list))))))
    (if (listp list) (rec list) list)))

(defun lazy-append (&rest lazy-lists
		    &aux (lazy-lists (mapcar #'make-lazy lazy-lists)))
  (labels ((rec (lazy-list rem)
	     (if lazy-list
		 (lazy-cons (lcar lazy-list)
			    (rec (lcdr lazy-list) rem))
		 (if rem
		     (rec (car rem) (cdr rem))
		     nil))))
    (rec (car lazy-lists) (cdr lazy-lists))))

(defun lazy-mapcar (function &rest args)
  (labels ((rec (args)
	     (if (every #'lcar args)
		 (lazy-cons (apply function (mapcar #'lcar args))
			    (rec (mapcar #'lcdr args)))
		 nil)))
    (rec (mapcar #'make-lazy args))))

(defun lazy-mapc (function &rest args)
  (labels ((rec (args)
	     (when (every #'identity args)
	       (progn (apply function (mapcar #'lcar args))
		      (rec (mapcar #'lcdr args))))))
    (rec (mapcar #'make-lazy args))))

(defun lazy-mapcan (function &rest args)
  (labels ((rec (args)
	     (if (every #'identity args)
		 (f (make-lazy (apply function (mapcar #'lcar args)))
		    (mapcar #'lcdr args))
		 nil))
	   (f (lst args)
	     (if lst
		 (lazy-cons (lcar lst)
			    (f (lcdr lst) args))
		 (rec args))))
    (rec (mapcar #'make-lazy args))))

(defun lazy-reduce (function arg &aux (cnt 0))
  (declare (fixnum cnt))
  (labels ((rec (lazy-list acc)
	     (when (> (incf cnt) #. (expt 10 6)) (setf cnt 0) (gc))
	     (if lazy-list
		 (rec (lcdr lazy-list) (funcall function acc (lcar lazy-list)))
		 acc)))
    (if (listp arg)
	(reduce function (release arg))
	(let ((first (lcar arg)))
	  (rec (release arg) first)))))

(defun force-list (lazy-list)
  (labels ((rec (lazy-list)
	     (when lazy-list
	       (cons (lcar lazy-list)
		     (rec (lcdr lazy-list))))))
    (if (listp lazy-list) lazy-list (rec (release lazy-list)))))

(defun lazy-take (n lazy-value)
  (labels ((rec (n value)
	     (if (or (null value) (<= n 0)) nil
		 (lazy-cons (lcar value)
			    (rec (1- n) (lcdr value))))))
    (rec n (make-lazy (release lazy-value)))))

(defun lazy-take-while (function lazy-value)
  (labels ((rec (value)
	     (when (and value
			(funcall function (lcar value)))
	       (lazy-cons (lcar value)
			  (rec (lcdr value))))))
    (rec (make-lazy lazy-value))))

(defun lazy-cdr-while (function lazy-value)
  (labels ((rec (value)
	     (cond ((null value)
		    nil)
		   ((funcall function (lcar value))
		    (rec (lcdr value)))
		   (t value))))
    (rec (make-lazy lazy-value))))

(defun lazy-length (lazy-value)
  (labels ((rec (value acc)
	     (if value
		 (rec (lcdr value) (1+ acc))
		 acc)))
    (if (listp lazy-value)
	(length (release lazy-value))
	(rec (release lazy-value) 0))))

(defun lazy-remove-if (function lazy-value)
  (labels ((rec (lazy-value)
	     (cond ((null lazy-value)
		    nil)
		   ((funcall function (lcar lazy-value))
		    (rec (lcdr lazy-value)))
		   (t (lazy-cons (lcar lazy-value)
				 (rec (lcdr lazy-value)))))))
    (rec (make-lazy lazy-value))))

(defmacro lazy-query (value &body body)
  `,(reduce (lambda (lazy-value query)
	      (case (car query)
		((map) `(lazy-mapcar
			 (lambda ,(nth 1 query) ,@(cddr query))
			 ,lazy-value))
		((reduce) `(lazy-reduce
			    (lambda ,(nth 1 query) ,@(cddr query))
			    ,lazy-value))
		((sum) `(lazy-reduce #'+ ,lazy-value))
		((remove-if) `(lazy-remove-if
			       (lambda ,(nth 1 query) ,@(cddr query))
			       ,lazy-value))
		((length) `(lazy-length ,lazy-value))
		((tolist) `(force-list ,lazy-value))
		((take) `(lazy-take ,(nth 1 query) ,lazy-value))
		((skip) `(nthlcdr ,(nth 1 query) ,lazy-value))
		((take-while) `(lazy-take-while
				(lambda ,(nth 1 query) ,@(cddr query))
				,lazy-value))
		((skip-while) `(lazy-cdr-while
				(lambda ,(nth 1 query) ,@(cddr query))
				,lazy-value))
		((append) `(lazy-mapcan #'identity ,lazy-value))))
	    body
	    :initial-value value))

(defmacro make-series (inits args &body body)
  (with-gensym (rec ans)
    `(labels ((,rec ,args
		(let ((,ans (progn ,@body)))
		  (lazy-cons ,ans
			     (,rec ,@(append (cdr args) (list ans)))))))
       (lazy-append ',inits (,rec ,@inits)))))

(defun map-a-b (function a b &optional (skip 1))
  (loop for i from a below b by skip collect (funcall function i)))
(defun map-0-n (function n &optional (skip 1))
  (loop for i from 0 below n by skip collect (funcall function i)))
(defun range-a-b (a b &optional (skip 1))
  (map-a-b #'identity a b skip))
(defun range-n (n &optional (skip 1))
  (map-0-n #'identity n skip))
(defun lazy-map-a-b (function a b &optional (skip 1))
  (labels ((rec (i)
	     (when (< i b)
	       (lazy-cons (funcall function i)
			  (rec (+ i skip))))))
    (rec a)))
(defun lazy-map-0-n (function n &optional (skip 1))
  (labels ((rec (i)
	     (when (< i n)
	       (lazy-cons (funcall function i)
			  (rec (+ i skip))))))
    (rec 0)))
(defun lazy-range-a-b (a b &optional (skip 1))
  (lazy-map-a-b #'identity a b skip))
(defun lazy-range-0-n (n &optional (skip 1))
  (lazy-map-0-n #'identity n skip))


(when
    t
  (time
   (print
    (lazy-query
	(lazy-range-0-n (expt 10 8))
      (sum)))))

(when
    nil
  (time
   (print
    (lazy-query
	(lazy-range-0-n (expt 10 7))
      (length)))))

(when
    nil
  (print (macroexpand-1 '(lazy-query
			  (lazy-range-0-n (expt 10 7))
			  (length)))))
