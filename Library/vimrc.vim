set nu sc ci si ai sw=4 ts=4 bs=2 ww=<,>,h,l noswapfile
set mouse=a
syntax on

let &g:makeprg="(g++ -o %:r %:r.cpp -O2 -Wl,-stack_size -Wl,0x10000000 -std=c++17 -Wall && time ./%:r < %:r.in)"
map  <F5> <ESC>:wa<CR>:make!<CR>:copen<CR>
imap <F5> <ESC>:wa<CR>:make!<CR>:copen<CR>

execute pathogen#infect()

syntax enable
set background=light
colorscheme solarized
