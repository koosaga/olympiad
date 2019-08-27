set nocp ai bs=2 hls ic is lbr ls=2 mouse=a nu ru sc scs smd so=3 sw=4 ts=4
filetype plugin indent on
syn on
map gA m'ggVG"+y''

com -range=% -nargs=1 P exe "<line1>,<line2>!".<q-args> |y|sil u|echom @"
com -range=% Hash <line1>,<line2>P tr -d '[:space:]' | md5sum
au FileType cpp com! -buffer -range=% Hash <line1>,<line2>P cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum
