ctags -R .
rm test
clear
gcc -o test read_write.c
./test
