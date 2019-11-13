syntax on
set number
set cursorline
set showmatch
set autoindent
set tabstop=4
set shiftwidth=4
set backspace=indent,eol,start
set clipboard=unnamedplus
set whichwrap=h,l,<,>,[,]
set nowrap

set swapfile
set directory=~/.vim_files
set backup
set backupdir=~/.vim_files
set undofile
set undodir=~/.vim_files

set scrolloff=10
set hlsearch
set matchpairs& matchpairs+=<:>

"set makeprg=make\ %:S\ -B
set makeprg=g++\ %:S

inoremap {<ENTER> {}<LEFT><CR><ESC><S-o>
inoremap jj <ESC>
inoremap , ,<SPACE>
inoremap qq <ESC>
inoremap /* /**/<LEFT><LEFT>
nnoremap <C-h> <LEFT>x
nnoremap <C-a> ggVG
nnoremap <C-i> mIggVG=`I
nnoremap x "_x
nnoremap s "_s
filetype on
augroup language
	autocmd!
	autocmd FileType cpp,c set cindent
	autocmd FileType cpp,c set cinkeys+=*;
	autocmd FileType cpp,c set cinoptions+=g0
	autocmd FileType cpp,c nnoremap <S-a> A;<ESC>=<CR>A<C-h>
	autocmd FileType cpp set syntax=cpp
	autocmd FileType cpp,c nnoremap <F4> <ESC>:w<CR>:silent make\|redraw!\|cc<CR><CR>
	autocmd FileType cpp,c nnoremap <F5> <ESC>:!makeinputs<CR>
	autocmd FileType cpp,c nnoremap <F6> <ESC>:w<CR>ggVGy:!testcase %<CR>:e ./test.out<CR>
	"autocmd BufWritePost *.cpp make
	"autocmd BufWritePre *.cpp normal ggVG=<CR>  "indent clearly
	autocmd FileType c set syntax=c
	autocmd FileType r setl cindent
	autocmd FileType r setl syntax=r
	autocmd FileType lisp nnoremap <F4> <ESC>:w<CR>:!clisp %<CR>
	autocmd FileType lisp nnoremap <F6> <ESC>:w<CR>ggVGy:!testlisp %<CR>:e ./test.out<CR>
augroup END

"this is get about atcoder input case
nnoremap <F7> :!getcase<CR>
