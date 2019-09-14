#!/bin/bash
time=`date "+%Y-%m-%d__%H:%M:%S"`

j=1
typ=(0 0 0 0 0 0 0 0 0 0 0)
ad=(0 0 0 0 0 0 0 0 0 0 )
for i in `lsblk -l -b|sed "1d"|tr -s " " ";"|cut -d ";" -f 6`; do
    if [[ $i = part ]]; then
        typ[$j]=0
    else
        typ[$j]=1
    fi
    j=$[$j+1]
done
k=1
for i in `lsblk -l -b|sed "1d"|tr -s " " ";"|cut -d ";" -f 7`; do
    ad[$k]="$i"
    echo $i
    k=$[$k+1]
done

for i in $(seq 1 $[$j-1]); do
    echo $time ${typ[$i]} ${ad[$k]}
done
