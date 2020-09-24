#!/bin/bash

num_dirs=0
dirnames="dirs32.txt"

for dirname1 in $(cat $dirnames)
do
    dirname2=$HOME/$dirname1
    ex_name=${dirname2##*/}
    ex_cmd=./$ex_name

    echo ""
    echo "---------- Running $ex_cmd ----------"

    cd $dirname2
    eval $ex_cmd
    echo ""

    num_dirs=$[$num_dirs + 1]
done

echo "num_dirs = $num_dirs"
