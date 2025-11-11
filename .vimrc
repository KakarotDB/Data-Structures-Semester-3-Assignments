set nocompatible  " Ensure Vim runs in modern mode
syntax on
colorscheme koehler " Ensure gruvbox is installed, or use 'desert' as a fallback
set complete+=kspell
set completeopt=menuone,longest
set spell  " Enable spell-checking for kspell
set cindent
set autoindent
let &t_SI = "\e[6 q"  " Set cursor to vertical bar in Insert mode (verify terminal support)
let &t_EI = "\e[2 q"  " Set cursor to block in Normal mode (verify terminal support)
set number
set tabstop=4
set shiftwidth=4
filetype plugin indent on
set showmode  " Display current mode (e.g., -- INSERT --)
augroup CBraceCompletion
  autocmd!
  autocmd FileType c inoremap <buffer> { {<CR>}<C-o>O
augroup END
