set nu sc ci si ai sw=4 ts=4 bs=2 ww=<,>,h,l noswapfile
set mouse=a
syntax on

let &g:makeprg="(g++ -o %:r %:r.cpp -O2 -std=c++11 -Wall && time ./%:r < %:r.in)"
map  <F5> <ESC>:wa<CR>:make!<CR>:copen<CR>
imap <F5> <ESC>:wa<CR>:make!<CR>:copen<CR>

syntax enable
set background=dark
colorscheme solarized

execute pathogen#infect()
