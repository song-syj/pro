;(require 'slime)
;(slime-setup)
;; setup load-path and autoloads
(add-to-list 'load-path "~/_emacs/slime-master")  
(require 'slime-autoloads)

;; Set your lisp system and, optionally, some contribs
(setq inferior-lisp-program "/usr/bin/sbcl")
(setq slime-contribs '(slime-fancy))
