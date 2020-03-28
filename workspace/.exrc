nnoremap  ggVG
let s:cpo_save=&cpo
set cpo&vim
nnoremap  <Left>x
nnoremap 	 mIggVG=`I
vmap [% [%m'gv``
vmap ]% ]%m'gv``
vmap a% [%v]%
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nnoremap j gj
nnoremap k gk
nnoremap s "_s
nnoremap x "_x
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
inoremap , , 
inoremap /* /**/<Left><Left>
inoremap jj 
inoremap qq 
inoremap { {}<Left>O
let &cpo=s:cpo_save
unlet s:cpo_save
set backup
set backupdir=~/.vim/backups
set clipboard=unnamedplus
set directory=~/.vim/backups
set expandtab
set helplang=en
set makeprg=g++\ %:S\ -Wall\ -Wextra\ -fsyntax-only\ -DDEBUG
set matchpairs=(:),{:},[:],<:>
set scrolloff=10
set shiftwidth=4
set showmatch
set tabstop=4
set undodir=~/.vim/backups
set undofile
set whichwrap=h,l,<,>,[,]
set window=40
" vim: set ft=vim :
