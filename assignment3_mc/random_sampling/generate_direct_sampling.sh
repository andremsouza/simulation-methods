#!/bin/bash
i=1
echo "particle_number,pi" > ./direct_sampling.csv

while [ $i -le 100000001 ]
do
    ./main_direct >> ./direct_sampling.csv $i
    echo "$i"
    i=$(($i + 100000))
done

./main_direct >> ./direct_sampling.csv $i
