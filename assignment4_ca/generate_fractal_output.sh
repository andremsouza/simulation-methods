#!/bin/bash
i=2
echo "p,t,r_gyration" > ./fractal_output.csv

while [ $i -le 8 ]
do
    j=0
    while [ $j -le 100 ]
    do
        ./dla_fraktal/main >> ./fractal_output.csv "0.$i"
        echo "$j"
        j=$(($j + 1))
    done
    echo "$i"
    i=$(($i + 3))
done
