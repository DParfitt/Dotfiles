"dein Scripts-----------------------------
if &compatible
  set nocompatible               " Be iMproved
endif

" Required:
set runtimepath+=/home/dillon/Templates/Neovim-Config/dein/repos/github.com/Shougo/dein.vim

" Required:
if dein#load_state('/home/dillon/Templates/Neovim-Config/dein')
  call dein#begin('/home/dillon/Templates/Neovim-Config/dein')

  " Let dein manage dein
  " Required:
  call dein#add('/home/dillon/Templates/Neovim-Config/dein/repos/github.com/Shougo/dein.vim')

  " Plugins
  call dein#add('junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' })
  call dein#add('junegunn/fzf.vim')
  call dein#add('tpope/vim-surround')
  call dein#add('tpope/vim-unimpaired')
  call dein#add('mattn/emmet-vim', { 'for': ['*html', '*css'] })
  call dein#add('tpope/vim-repeat') 
  call dein#add('godlygeek/tabular')
  call dein#add('lambdalisue/vim-manpager')
  call dein#add('scrooloose/nerdtree')
  call dein#add('airblade/vim-gitgutter')
  call dein#add('junegunn/rainbow_parentheses.vim')
  call dein#add('rhysd/open-pdf.vim')
  call dein#add('jiangmiao/auto-pairs')
  call dein#add('w0rp/ale')
  call dein#add('wellle/targets.vim')
  call dein#add('chriskempson/base16-vim')
  call dein#add('christoomey/vim-tmux-navigator')
  call dein#add('lervag/vimtex')
"  Required:
  call dein#end()
  call dein#save_state()
endif

" Required:
filetype plugin indent on
syntax enable

" Install on startup
if dein#check_install()
  call dein#install()
endif

"End dein Scripts-------------------------


" augroups
augroup indents
	autocmd!
	autocmd FileType less,css,html setlocal ts=2 sts=2 sw=2 expandtab
	autocmd FileType text,markdown setlocal expandtab
	autocmd FileType python setlocal ts=4 sts=4 sw=4 noexpandtab
augroup END


augroup highlight_follows_vim
	autocmd!
	autocmd FocusGained * set cursorline
	autocmd FocusLost * set nocursorline
augroup END

augroup status
	au InsertEnter * call InsertStatuslineColor(v:insertmode)
	au InsertChange * call InsertStatuslineColor(v:insertmode)
	au InsertLeave * hi PrimaryBlock ctermbg=4
augroup END


augroup mapppings
	autocmd!
	autocmd FileType less,css,html nnoremap <Leader>s viB:sort<cr>
augroup END

augroup restorecursor
	autocmd BufReadPost *
		\ if line("'\"") > 1 && line("'\"") <= line("$") |
		\   execute "normal! g`\"" |
		\ endif
augroup END

augroup nerdtree
	autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
augroup END


" general settings
set nobackup
set nowritebackup
set noswapfile " get rid of swapfiles everywhere
set dir=/tmpset

syntax on

set omnifunc=syntaxcomplete#Complete
set list
filetype indent on
set number
set laststatus=2
set nowrap
set noshowmode
set listchars=tab:│\ ,nbsp:␣,trail:∙,extends:>,precedes:<,eol:¬
set fillchars=vert:\│
set scrolloff=3
set ignorecase
set smartcase
set sidescroll=40
set incsearch
set hlsearch
set undofile
set undodir=~/tmp
set path+=**
set inccommand=split
set backspace=indent,eol,start
set hidden
set wildmenu
set foldmethod=manual
set complete=.,w,b,i,u,t,

set wildignore+=.git,.hg,.svn
set wildignore+=*.aux,*.out,*.toc
set wildignore+=*.o,*.obj,*.exe,*.dll,*.manifest,*.rbc,*.class
set wildignore+=*.ai,*.bmp,*.gif,*.ico,*.jpg,*.jpeg,*.png,*.psd,*.webp
set wildignore+=*.avi,*.divx,*.mp4,*.webm,*.mov,*.m2ts,*.mkv,*.vob,*.mpg,*.mpeg
set wildignore+=*.mp3,*.oga,*.ogg,*.wav,*.flac
set wildignore+=*.eot,*.otf,*.ttf,*.woff
set wildignore+=*.doc,*.pdf,*.cbr,*.cbz
set wildignore+=*.zip,*.tar.gz,*.tar.bz2,*.rar,*.tar.xz,*.kgb
set wildignore+=*.swp,.lock,.DS_Store,._*

let g:base16_shell_path='~/.config/nvim/colors/'
let base16colorspace=256
colorscheme base16-nord
hi Normal ctermbg=NONE guibg=NONE

set shiftwidth=4     " indent = 4 spaces
set noexpandtab      " tabs are tabs
set tabstop=4        " tab = 4 spaces
set softtabstop=4    " backspace through spaces


" statusline
let g:currentmode={
    \ 'n'  : 'NORMAL ',
    \ 'no' : 'N·OPERATOR PENDING ',
    \ 'v'  : 'VISUAL ',
    \ 'V'  : 'V·LINE ',
    \ '' : 'V·BLOCK ',
    \ 's'  : 'SELECT ',
    \ 'S'  : 'S·LINE ',
    \ '' : 'S·BLOCK ',
    \ 'i'  : 'INSERT ',
    \ 'R'  : 'REPLACE ',
    \ 'Rv' : 'V·REPLACE ',
    \ 'c'  : 'COMMAND ',
    \ 'cv' : 'VIM EX ',
    \ 'ce' : 'EX ',
    \ 'r'  : 'PROMPT ',
    \ 'rm' : 'MORE ',
    \ 'r?' : 'CONFIRM ',
    \ '!'  : 'SHELL ',
    \ 't'  : 'TERMINAL '}


set statusline=
set statusline+=%#PrimaryBlock#
set statusline+=\ %{g:currentmode[mode()]}
" set statusline+=%#SecondaryBlock#
set statusline+=%{StatuslineGit()}
" set statusline+=%#Blanks#
set statusline+=\ %t\ 
set statusline+=%(%m%)
" set statusline+=%#PrimaryBlock#
set statusline+=%=
set statusline+=Ln
set statusline+=\ %l
set statusline+=,Col
set statusline+=\ %c
set statusline+=\ \ \ %Y\ 

function! InsertStatuslineColor(mode)
  if a:mode == 'i'
    hi PrimaryBlock ctermbg=2
  elseif a:mode == 'r'
    hi PrimaryBlock ctermbg=6
  else
    hi PrimaryBlock ctermbg=3
  endif
endfunction

" default the statusline to green when entering Vim
hi PrimaryBlock ctermbg=8

function! GitBranch()
	return system("git rev-parse --abbrev-ref HEAD 2>/dev/null | tr -d '\n'")
endfunction

function! StatuslineGit()
	let l:branchname = GitBranch()
	return strlen(l:branchname) > 0?'  '.l:branchname.' ':''
endfunction


" Functions
function! GetTabber()  " a lil function that integrates well with Tabular.vim
	let c = nr2char(getchar())
	:execute 'Tabularize /' . c
endfunction

let g:help_in_tabs = 1

nmap <silent> H  :let g:help_in_tabs = !g:help_in_tabs<CR>

" Only apply to .txt files...
augroup HelpInTabs
	autocmd!
	autocmd BufEnter  *.txt   call HelpInNewTab()
augroup END

" Only apply to help files...
function! HelpInNewTab ()
	if &buftype == 'help' && g:help_in_tabs
		"Convert the help window to a tab...
		execute "normal \<C-W>T"
	endif
endfunction


" mappings
let mapleader=' '
let maplocalleader=','

" inoremaps
augroup rustSemi
	autocmd!
	autocmd FileType rust inoremap ;; <esc><S-a>;
augroup END


" nnoremap
nnoremap <Leader>o : only<cr>
nnoremap <Leader>l : Lines<cr>
nnoremap <Leader>b : Buffers<cr>
nnoremap <Leader>z : FZF<cr>
nnoremap <Leader>w : MtaJumpToOtherTag<cr>
nnoremap <Leader>t : call GetTabber()<cr>
nnoremap <Leader>n : tabnext<cr>
nnoremap <Leader>N : tabprevious<cr>
nnoremap <Leader>r : RustRun<cr>
nnoremap <Leader><ESC> : nohlsearch<cr>
nnoremap <F2>      : NERDTreeToggle<cr>
nnoremap <C-l> :nohlsearch<cr>:diffupdate<cr>:syntax sync fromstart<cr><c-l>
nnoremap H H:exec 'norm! '. &scrolloff . 'k'<cr>
nnoremap L L:exec 'norm! '. &scrolloff . 'j'<cr>
nnoremap  <expr> gb '`[' . strpart(getregtype(), 0, 1) . '`]'

map <F10> :echo "hi<" . synIDattr(synID(line("."),col("."),1),"name") . '> trans<'
			\ . synIDattr(synID(line("."),col("."),0),"name") . "> lo<"
			\ . synIDattr(synIDtrans(synID(line("."),col("."),1)),"name") . ">"<CR>

cmap w!! %!sudo tee > /dev/null %

" vnoremap
vnoremap > >gv
vnoremap < <gv

" onoremap
onoremap ax a`
onoremap ix i`

" xnoremap
xnoremap + g<C-b>
xnoremap - g<C-x>

:command! WQ wq
:command! Wq wq
:command! Wqa wqa
:command! W w
:command! Q q

" abbreviations
abclear
iab #i #include
iab #d #define
cab dst put =strftime('%d %a, %b %Y')<cr>
cab vg vimgrep


" plugin settings
" emmet
let g:user_emmet_mode='a'
let g:user_emmet_leader_key='<C-X>'

" Vimtex
call vimtex#imaps#add_map({'lhs':'/','rhs':'\frac','wrapper':'vimtex#imaps#wrap_math'})
let g:tex_flavor = 'latex'
let g:vimtex_view_method='zathura'
let g:vimtex_latexmk_progname='nvr'
let vimtex_view_zathura_options=''
nnoremap <localleader>wc :VimtexWordCount<cr>
"


" nerdtree
let g:NERDTreeMinimalUI           = 1
let g:NERDTreeWinPos              = 'left'
let g:NERDTreeStatusline          = -1
let g:NERDTreeDirArrowExpandable  = '+'
let g:NERDTreeDirArrowCollapsible = '-'

" gitgutter
let g:gitgutter_override_sign_column_highlight = 0
let g:gitgutter_sign_added                     = '+'
let g:gitgutter_sign_modified                  = '±'
let g:gitgutter_sign_removed                   = '-'
let g:gitgutter_sign_removed_first_line        = '^'
let g:gitgutter_sign_modified_removed          = '#'

" ale
let g:ale_use_deprecated_neovim = 1
let g:ale_sign_error            = 'x'
let g:ale_sign_warning          = 'o'
let g:ale_set_highlights = 0

let g:ale_linters = {'python': ['pylint']}
