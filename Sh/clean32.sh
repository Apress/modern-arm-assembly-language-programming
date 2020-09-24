#!/bin/bash

num_dirs=0
dirnames="dirs32.txt"

for dirname1 in $(cat $dirnames)
do
    dirname2=$HOME/$dirname1
    cd $dirname2

    echo "running make clean in $dirname2"
    make clean
    echo ""

    num_dirs=$[$num_dirs + 1]
done

echo "num_dirs = $num_dirs"
