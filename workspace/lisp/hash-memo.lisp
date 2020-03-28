#-swank
(unless (member :child-sbcl *features*)
  (quit
   :unix-status
   (process-exit-code
    (run-program *runtime-pathname*
                 `("--control-stack-size" "128MB"
                   "--noinform" "--disable-ldb" "--lose-on-corruption" "--end-runtime-options"
                   "--eval" "(push :child-sbcl *features*)"
                   "--script" ,(namestring *load-pathname*))
                 :output t :error t :input t))))


(defparameter *hash-memo* (make-hash-table :test #'equal))

(defmacro dp (&body func)
  `(let* ((f (quote func))
          (num (gethash f *hash-memo*)))
     (if num
       num
       (setf (gethash f *hash-memo*) ,func))))

(defun factorial (x)
  (if (<= x 1) 1
    (mod (* x (factorial (1- x))) 100)))

(defun fibonacchi (x)
  (if (<= x 1) 1
    (mod 
    (+ (dp fibonacchi (1- x)) (dp fibonacchi (- x 2))) 100)))

(print (dp factorial (read)))
