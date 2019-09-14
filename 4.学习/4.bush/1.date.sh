#! /bin/bash 
temp=1
year=$1
yue=$2
ri=$3

if [ "$year" -eq 0 -o "$yue" -eq 0 -o "$ri" -eq 0 ]
then temp=0
    echo NO1
    exit 0
fi


let "y1=$year % 4"
let "y2=$year % 100"
let "y3=$year % 400"
if [ ! "$y1" -eq 0 ]
then
leap=0
elif [ ! "$y2" -eq 0 ]
then
leap=1
elif [ "$y3" -eq 0 ]
then
leap=1
else
leap=0
fi


if [ "$leap" -eq 1 -a "$yue" -eq 2 -a "$ri" -gt 29 ]
then temp=0
echo NO2
exit 0
fi

if [ "$leap" -eq 0 -a "$yue" -eq 2 -a "$ri" -gt 28 ]
then temp=0
echo NO3
exit 0
fi


if [ "$yue" -eq 1 -o "$yue" -eq 3 -o "$yue" -eq 5 -o "$yue" -eq 7 -o "$yue" -eq 8 -o "$yue" -eq 10 -o "$yue" -eq 12 ]
    then 
        if [ "$ri" -gt 31 ]
        then temp=0
            echo NO4
            exit 0
        fi
    fi

if [ "$yue" -eq 4 -o "$yue" -eq 6 -o "$yue" -eq 9 -o "$yue" -eq 11 -a "$ri" -gt 30 ]
then temp=0
echo NO5
exit 0
fi

echo YES
exit 1
