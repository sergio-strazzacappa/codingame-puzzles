#! /bin/bash

read n

horses=()

for (( i=0; i<$n; i++ )); do
    read pi
    horses[i]=$pi
done

IFS=$'\n' sorted=($(sort -n <<<"${horses[*]}"))

closest=9999;

for (( i=0; i<$n-1; i++ )); do
    dif=$((${sorted[$i+1]}-${sorted[$i]}))
    if [ $dif -lt $closest ]; then
        closest=$dif
    fi
done

echo $closest
