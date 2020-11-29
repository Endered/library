#-swank
(unless (member :child-sbcl *features*)
  "I refered from https://competitive12.blogspot.com/2020/03/common-lisp.html thank you!"
  (quit
   :unix-status
   (process-exit-code
    (run-program *runtime-pathname*
                 `("--control-stack-size" "256MB"
                   "--noinform" "--disable-ldb" "--lose-on-corruption" "--end-runtime-options"
                   "--eval" "(push :child-sbcl *features*)"
                   "--script" ,(namestring *load-pathname*))
                 :output t :error t :input t))))
(defmacro dpline (name args memo-size &body body)
  (let ((memo (gensym)))
    `(let ((,memo (make-array ,memo-size :initial-element nil)))
       (defun ,name ,args
         (or (aref ,memo ,@args)
             (setf (aref ,memo ,@args)
                   ,@body))))))

(defmacro dphash (name args &body expr)
  `(let ((table (make-hash-table :test #'equal)))
     (defun  ,name ,args 
       (or (gethash (list ,@args) table)
           (setf (gethash (list ,@args) table)
                 (progn 
                   ,@expr))))))

(defun split (x str)
  (let ((pos (search x str))
        (size (length x)))
    (if pos
        (cons (subseq str 0 pos)
              (split x (subseq str (+ pos size))))
        (list str))))

(defmacro collect-times (time body)
  `(loop repeat ,time collect ,body))

(defun read-times (time)
  (collect-times time (read)))

(defmacro aif (expr then else)
  `(let ((it ,expr))
     (if it ,then ,else)))

(defmacro awhen (expr &rest then)
  `(aif ,expr (progn ,@then) nil))

(defun comulative (function list &key base)
  (if base
      (comulative function (cons base list))
      (do ((lst (cdr list) (cdr lst))
           (acc (list (car list))))
          ((null lst) (reverse acc))
        (push (funcall function (car acc) (car lst)) acc))))

(defun binary-search (function left right
                      &optional
                        (eps 1)
                        (average-function (lambda (x y) (ash (+ x y) -1))))
  (if (<= (abs (- left right)) eps)
      right
      (let ((mid (funcall average-function left right)))
        (if (funcall function mid)
            (binary-search function left mid eps average-function)
            (binary-search function mid right eps average-function)))))

(defun arithmetic-mean (&rest body)
  (/ (apply #'+ body) (length body)))

(defvar +MOD+ (+ (expt 10 9) 7))

(defun range-0-n (n &optional (step 1))
  (loop for i from 0 below n by step collect i))

(defun range-1-n (n &optional (step 1))
  (loop for i from 1 below n by step collect i))

(defun range-a-b (a b &optional (step 1))
  (loop for i from a below b by step collect i))

(defun map-0-n (function n &optional (step 1))
  (mapcar function (range-0-n n step)))

(defun map-1-n (function n &optional (step 1))
  (mapcar function (range-1-n n step)))

(defun map-a-b (function a b &optional (step 1))
  (mapcar function (range-a-b a b step)))

(defun read-string (&optional (stream *standard-input*))
  (labels ((is-empty (x)
             (or (char= x #\space) (char= x #\newline))))
    (loop for char = (read-char stream)
          with result
          when (and result (is-empty char))
            do (return (concatenate 'string (nreverse result)))
          when (null (is-empty char))
            do (push char result))))

(defun merge-sort (lst &optional (compare #'<))
  (let ((turn 0))
    (labels ((merge-list (a b a-length b-length)
               (cond ((zerop a-length) b)
                     ((zerop b-length) a)
                     ((funcall compare (car b) (car a))
                      (incf turn a-length)
                      (cons (car b)
                            (merge-list a (cdr b) a-length (1- b-length))))
                     (t
                      (cons (car a)
                            (merge-list (cdr a) b (1- a-length) b-length)))))
             (f (lst length)
               (if (= length 1)
                   lst
                   (let ((mid (ash length -1)))
                     (merge-list (f (subseq lst 0 mid) mid)
                                 (f (subseq lst mid) (- length mid))
                                 mid
                                 (- length mid))))))
      (values (f lst (length lst)) turn))))

(defun group (lst &optional (test #'eql) (key nil))
  (let ((table (make-hash-table :test test)))
    (mapc (lambda (x)
            (push x (gethash (if key (funcall key x) x) table)))
          lst)
    (loop for value being each hash-value in table
          collect value)))

(defun nearby (&rest args)
  (let ((current (subseq args 0 (ash (length args) -1)))
        (validator (subseq args (ash (length args) -1)))
        (res nil))
    (labels ((check ()
               (every (lambda (x y) (and (<= 0 x) (< x y)))
                      current validator))
             (f (lst)
               (unless lst (return-from f))
               (let ((x (car lst)))
                 (setf (car lst) (1+ x))
                 (when (check) (push (copy-list current) res))
                 (setf (car lst) (1- x))
                 (when (check) (push (copy-list current) res))
                 (setf (car lst) x))
               (f (cdr lst))))
      (f current)
      res)))

(defun make-primes (max-number)
  (let ((array (make-array (1+ max-number) :initial-element t)))
    (loop for i from 2 to max-number
          for is-prime = (aref array i)
          when is-prime collect i
          when is-prime
          do (loop for j from (* 2 i) to max-number by i
                   do (setf (aref array j) nil)))))

(defun make-is-prime (max-number)
  (let ((primes (make-primes max-number))
        (table (make-array (1+ max-number) :initial-element nil)))
    (dolist (i primes)
      (setf (aref table i) t))
    (defun is-prime (x)
      (aref table x))))


(defparameter +MOD+ (print (+ 7 (expt 10 9))))
(defmacro mod+ (&body args)
  (reduce (lambda (a b) `(mod (+ ,a ,b) +MOD+))
          args))
(defmacro mod- (&body args)
  (reduce (lambda (a b) `(mod (- ,a ,b) +MOD+))
          args))
(defmacro mod* (&body args)
  (reduce (lambda (a b) `(mod (* ,a ,b) +MOD+))
          args))
(defun modpow (base power)
  (if (zerop power)
      1
      (let ((base2 (mod* base base)))
        (mod* (if (oddp power) base 1)
              (modpow base2 (ash power -1))))))
(defun modinv (x)
  (modpow x (- +MOD+ 2)))
(defmacro mod/ (x &body args)
  `(mod* ,x 
         (modinv (mod* ,@args))))
