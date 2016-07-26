set nu sc ci si ai sw=4 ts=4 bs=2 ww=<,>,h,l noswapfile
set mouse=a
syntax on

let &g:makeprg="(g++ -o %:r %:r.cpp -O2 -std=c++11 -Wall && time ./%:r < %:r.in)"

syntax enable
set background=dark
colorscheme solarized
