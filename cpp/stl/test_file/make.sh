#!/bin/bash

mkdir -p bin

gcc 01_mkchrmdir.c -o bin/mkchrmdir
gcc 02_copyfile.c -o bin/cp
gcc 03_appendfile.c -o bin/append
gcc 04_fwr.c -o bin/fwr
gcc 05_formatIO.c -o bin/formatIO
gcc 06_eof.c -o bin/eof
gcc 07_setbuf.c -o bin/setbuf
gcc 08_print.c -o bin/p
