(add-to-list 'load-path "~/_emacs/yasnippet")
(require 'yasnippet)
(yas/global-mode 1)

(add-to-list 'load-path "~/_emacs/auto-complete") 
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories "~/_emacs/auto-comlete/ac-dict")
(ac-config-default)
