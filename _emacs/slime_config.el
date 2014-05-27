;(require 'slime)
;(slime-setup)
;; setup load-path and autoloads
(add-to-list 'load-path "~/_emacs/slime-master")  
(require 'slime-autoloads)

;; Set your lisp system and, optionally, some contribs
(setq inferior-lisp-program "/usr/bin/sbcl")
(setq slime-contribs '(slime-fancy))

;; (require 'rainbow-delimiters)
;; (add-hook 'lisp-mode-hook 'rainbow-delimiters-mode)

(add-hook 'lisp-mode-hook
  (lambda ()
    (paredit-mode 1)))


;; (require 'autopair)
;; (autopair-global-mode) ;; enable autopair in all buffers
