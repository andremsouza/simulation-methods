#!/bin/bash
i=1
echo "type,particle_number,time" > ./opt_none/opt_none.csv
echo "type,particle_number,time" > ./opt_verlet/opt_verlet.csv
echo "type,particle_number,time" > ./opt_verlet_tabulated/opt_verlet_tabulated.csv
while [ $i -le 32768 ]
do
    echo -n '0,' >> ./opt_none/opt_none.csv
    ./opt_none/main false $i >> ./opt_none/opt_none.csv
    echo -n '1,' >> ./opt_verlet/opt_verlet.csv
    ./opt_verlet/main false $i >> ./opt_verlet/opt_verlet.csv
    echo -n '2,' >> ./opt_verlet_tabulated/opt_verlet_tabulated.csv
    ./opt_verlet_tabulated/main false $i >> ./opt_verlet_tabulated/opt_verlet_tabulated.csv
    echo "$i"
    i=$(($i * 2))
done
