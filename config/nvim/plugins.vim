set rtp+=~/.config/nvim/bundle/Vundle.vim

call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'itchyny/lightline.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'junegunn/fzf'
Plugin 'junegunn/fzf.vim'
Plugin 'danro/rename.vim'
Plugin 'terryma/vim-multiple-cursors'
Plugin 'w0rp/ale'
Plugin 'editorconfig/editorconfig-vim'
Plugin 'airblade/vim-gitgutter'
Plugin 'tpope/vim-surround'
Plugin 'joshdick/onedark.vim'
Plugin 'christoomey/vim-tmux-navigator'
Plugin 'Python-mode-klen'
Plugin 'valloric/youcompleteme'
Plugin 'shougo/dein.vim'
Plugin 'alnjxn/base16-oceanicnext'

call vundle#end()

filetype plugin indent on

let g:pymode_python = 'python3'
